﻿#include "monster/pet-fall-off.h"
#include "cmd/cmd-pet.h" // 暫定、定数を見ているだけなのでutilへの分離を検討する.
#include "floor/floor.h"
#include "io/targeting.h"
#include "player/player-damage.h"
#include "player/player-move.h"
#include "player/player-skill.h"

/*!
 * @brief モンスターから直接攻撃を受けた時に落馬するかどうかを判定し、判定アウトならば落馬させる
 * @param target_ptr プレーヤーへの参照ポインタ
 * @param monap_ptr モンスターからプレーヤーへの直接攻撃構造体への参照ポインタ
 * @return なし
 */
void check_fall_off_horse(player_type *target_ptr, monap_type *monap_ptr)
{
    if ((target_ptr->riding == 0) || (monap_ptr->damage == 0))
        return;

    char m_steed_name[MAX_NLEN];
    monster_desc(target_ptr, m_steed_name, &target_ptr->current_floor_ptr->m_list[target_ptr->riding], 0);
    if (process_fall_off_horse(target_ptr, (monap_ptr->damage > 200) ? 200 : monap_ptr->damage, FALSE))
        msg_format(_("%^sから落ちてしまった！", "You have fallen from %s."), m_steed_name);
}

/*!
 * @brief プレイヤーの落馬判定処理
 * @param dam 落馬判定を発した際に受けたダメージ量
 * @param force TRUEならば強制的に落馬する
 * @return 実際に落馬したらTRUEを返す
 */
bool process_fall_off_horse(player_type *creature_ptr, HIT_POINT dam, bool force)
{
    POSITION sy = 0, sx = 0;
    int sn = 0;
    GAME_TEXT m_name[MAX_NLEN];
    monster_type *m_ptr = &creature_ptr->current_floor_ptr->m_list[creature_ptr->riding];
    monster_race *r_ptr = &r_info[m_ptr->r_idx];

    if (!creature_ptr->riding)
        return FALSE;
    if (creature_ptr->wild_mode)
        return FALSE;

    if (dam >= 0 || force) {
        if (!force) {
            int cur = creature_ptr->skill_exp[GINOU_RIDING];
            int max = s_info[creature_ptr->pclass].s_max[GINOU_RIDING];
            int ridinglevel = r_ptr->level;

            /* 落馬のしやすさ */
            int fall_off_level = r_ptr->level;
            if (creature_ptr->riding_ryoute)
                fall_off_level += 20;

            if ((cur < max) && (max > 1000) && (dam / 2 + ridinglevel) > (cur / 30 + 10)) {
                int inc = 0;
                if (ridinglevel > (cur / 100 + 15))
                    inc += 1 + (ridinglevel - cur / 100 - 15);
                else
                    inc += 1;

                creature_ptr->skill_exp[GINOU_RIDING] = MIN(max, cur + inc);
            }

            /* レベルの低い乗馬からは落馬しにくい */
            if (randint0(dam / 2 + fall_off_level * 2) < cur / 30 + 10) {
                if ((((creature_ptr->pclass == CLASS_BEASTMASTER) || (creature_ptr->pclass == CLASS_CAVALRY)) && !creature_ptr->riding_ryoute)
                    || !one_in_(creature_ptr->lev * (creature_ptr->riding_ryoute ? 2 : 3) + 30)) {
                    return FALSE;
                }
            }
        }

        /* Check around the player */
        for (DIRECTION i = 0; i < 8; i++) {
            POSITION y = creature_ptr->y + ddy_ddd[i];
            POSITION x = creature_ptr->x + ddx_ddd[i];

            grid_type *g_ptr;
            g_ptr = &creature_ptr->current_floor_ptr->grid_array[y][x];

            if (g_ptr->m_idx)
                continue;

            /* Skip non-empty grids */
            if (!cave_have_flag_grid(g_ptr, FF_MOVE) && !cave_have_flag_grid(g_ptr, FF_CAN_FLY)) {
                if (!player_can_ride_aux(creature_ptr, g_ptr, FALSE))
                    continue;
            }

            if (cave_have_flag_grid(g_ptr, FF_PATTERN))
                continue;

            /* Count "safe" grids */
            sn++;

            /* Randomize choice */
            if (randint0(sn) > 0)
                continue;

            /* Save the safe location */
            sy = y;
            sx = x;
        }

        if (!sn) {
            monster_desc(creature_ptr, m_name, m_ptr, 0);
            msg_format(_("%sから振り落とされそうになって、壁にぶつかった。", "You have nearly fallen from %s, but bumped into wall."), m_name);
            take_hit(creature_ptr, DAMAGE_NOESCAPE, r_ptr->level + 3, _("壁への衝突", "bumping into wall"), -1);
            return FALSE;
        }

        POSITION old_y = creature_ptr->y;
        POSITION old_x = creature_ptr->x;
        creature_ptr->y = sy;
        creature_ptr->x = sx;
        lite_spot(creature_ptr, old_y, old_x);
        lite_spot(creature_ptr, creature_ptr->y, creature_ptr->x);
        verify_panel(creature_ptr);
    }

    creature_ptr->riding = 0;
    creature_ptr->pet_extra_flags &= ~(PF_TWO_HANDS);
    creature_ptr->riding_ryoute = creature_ptr->old_riding_ryoute = FALSE;

    creature_ptr->update |= (PU_BONUS | PU_VIEW | PU_LITE | PU_FLOW | PU_MON_LITE | PU_MONSTERS);
    handle_stuff(creature_ptr);

    creature_ptr->window |= (PW_OVERHEAD | PW_DUNGEON);
    creature_ptr->redraw |= (PR_EXTRA);

    /* Update health track of mount */
    creature_ptr->redraw |= (PR_UHEALTH);

    bool fall_dam = FALSE;
    if (creature_ptr->levitation && !force) {
        monster_desc(creature_ptr, m_name, m_ptr, 0);
        msg_format(_("%sから落ちたが、空中でうまく体勢を立て直して着地した。", "You are thrown from %s, but make a good landing."), m_name);
    } else {
        take_hit(creature_ptr, DAMAGE_NOESCAPE, r_ptr->level + 3, _("落馬", "Falling from riding"), -1);
        fall_dam = TRUE;
    }

    if (sy && !creature_ptr->is_dead)
        (void)move_player_effect(creature_ptr, creature_ptr->y, creature_ptr->x, MPE_DONT_PICKUP | MPE_DONT_SWAP_MON);

    return fall_dam;
}