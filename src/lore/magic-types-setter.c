﻿#include "lore/magic-types-setter.h"
#include "lore/lore-calculator.h"
#include "monster-race/race-flags-ability1.h"
#include "monster-race/race-flags-ability2.h"
#include "monster-race/race-flags4.h"
#include "mspell/mspell-type.h"
#include "term/term-color-types.h"

void set_breath_types(player_type *player_ptr, lore_type *lore_ptr)
{
    lore_ptr->vn = 0;
    if (lore_ptr->flags4 & (RF4_BR_ACID)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_ACID), _("酸%s", "acid%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_GREEN;
    }

    if (lore_ptr->flags4 & (RF4_BR_ELEC)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_ELEC), _("稲妻%s", "lightning%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_BLUE;
    }

    if (lore_ptr->flags4 & (RF4_BR_FIRE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_FIRE), _("火炎%s", "fire%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_RED;
    }

    if (lore_ptr->flags4 & (RF4_BR_COLD)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_COLD), _("冷気%s", "frost%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }

    if (lore_ptr->flags4 & (RF4_BR_POIS)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_POIS), _("毒%s", "poison%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_GREEN;
    }

    if (lore_ptr->flags4 & (RF4_BR_NETH)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_NETHER), _("地獄%s", "nether%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_DARK;
    }

    if (lore_ptr->flags4 & (RF4_BR_LITE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_LITE), _("閃光%s", "light%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_YELLOW;
    }

    if (lore_ptr->flags4 & (RF4_BR_DARK)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_DARK), _("暗黒%s", "darkness%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_DARK;
    }

    if (lore_ptr->flags4 & (RF4_BR_CONF)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_CONF), _("混乱%s", "confusion%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_UMBER;
    }

    if (lore_ptr->flags4 & (RF4_BR_SOUN)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_SOUND), _("轟音%s", "sound%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_ORANGE;
    }

    if (lore_ptr->flags4 & (RF4_BR_CHAO)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_CHAOS), _("カオス%s", "chaos%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_VIOLET;
    }

    if (lore_ptr->flags4 & (RF4_BR_DISE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_DISEN), _("劣化%s", "disenchantment%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_VIOLET;
    }

    if (lore_ptr->flags4 & (RF4_BR_NEXU)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_NEXUS), _("因果混乱%s", "nexus%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_VIOLET;
    }

    if (lore_ptr->flags4 & (RF4_BR_TIME)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_TIME), _("時間逆転%s", "time%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_BLUE;
    }

    if (lore_ptr->flags4 & (RF4_BR_INER)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_INERTIA), _("遅鈍%s", "inertia%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_SLATE;
    }

    if (lore_ptr->flags4 & (RF4_BR_GRAV)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_GRAVITY), _("重力%s", "gravity%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_SLATE;
    }

    if (lore_ptr->flags4 & (RF4_BR_SHAR)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_SHARDS), _("破片%s", "shards%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_UMBER;
    }

    if (lore_ptr->flags4 & (RF4_BR_PLAS)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_PLASMA), _("プラズマ%s", "plasma%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_RED;
    }

    if (lore_ptr->flags4 & (RF4_BR_WALL)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_FORCE), _("フォース%s", "force%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_UMBER;
    }

    if (lore_ptr->flags4 & (RF4_BR_MANA)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_MANA), _("魔力%s", "mana%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_BLUE;
    }

    if (lore_ptr->flags4 & (RF4_BR_NUKE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_NUKE), _("放射性廃棄物%s", "toxic waste%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_GREEN;
    }

    if (lore_ptr->flags4 & (RF4_BR_DISI)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BR_DISI), _("分解%s", "disintegration%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_SLATE;
    }
}

void set_ball_types(player_type *player_ptr, lore_type *lore_ptr)
{
    if (lore_ptr->a_ability_flags1 & (RF5_BA_ACID)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_ACID), _("アシッド・ボール%s", "produce acid balls%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_GREEN;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_ELEC)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_ELEC), _("サンダー・ボール%s", "produce lightning balls%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_BLUE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_FIRE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_FIRE), _("ファイア・ボール%s", "produce fire balls%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_RED;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_COLD)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_COLD), _("アイス・ボール%s", "produce frost balls%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_POIS)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_POIS), _("悪臭雲%s", "produce poison balls%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_GREEN;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_NETH)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_NETHER), _("地獄球%s", "produce nether balls%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_DARK;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_WATE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_WATER), _("ウォーター・ボール%s", "produce water balls%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_BLUE;
    }

    if (lore_ptr->flags4 & (RF4_BA_NUKE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_NUKE), _("放射能球%s", "produce balls of radiation%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_GREEN;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_MANA)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_MANA), _("魔力の嵐%s", "invoke mana storms%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_BLUE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_DARK)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_DARK), _("暗黒の嵐%s", "invoke darkness storms%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_DARK;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BA_LITE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_STARBURST), _("スターバースト%s", "invoke starburst%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_YELLOW;
    }

    if (lore_ptr->flags4 & (RF4_BA_CHAO)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BALL_CHAOS), _("純ログルス%s", "invoke raw Logrus%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_VIOLET;
    }
}

void set_particular_types(player_type *player_ptr, lore_type *lore_ptr)
{
    if (lore_ptr->a_ability_flags2 & (RF6_HAND_DOOM)) {
        lore_ptr->vp[lore_ptr->vn] = _("破滅の手(40%-60%)", "invoke the Hand of Doom(40%-60%)");
        lore_ptr->color[lore_ptr->vn++] = TERM_VIOLET;
    }

    if (lore_ptr->a_ability_flags2 & (RF6_PSY_SPEAR)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_PSY_SPEAR), _("光の剣%s", "psycho-spear%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_YELLOW;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_DRAIN_MANA)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_DRAIN_MANA), _("魔力吸収%s", "drain mana%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_SLATE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_MIND_BLAST)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_MIND_BLAST), _("精神攻撃%s", "cause mind blasting%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_RED;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BRAIN_SMASH)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BRAIN_SMASH), _("脳攻撃%s", "cause brain smashing%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_RED;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_CAUSE_1)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_CAUSE_1), _("軽傷＋呪い%s", "cause light wounds and cursing%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_CAUSE_2)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_CAUSE_2), _("重傷＋呪い%s", "cause serious wounds and cursing%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_CAUSE_3)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_CAUSE_3), _("致命傷＋呪い%s", "cause critical wounds and cursing%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_CAUSE_4)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_CAUSE_4), _("秘孔を突く%s", "cause mortal wounds%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }
}

void set_bolt_types(player_type *player_ptr, lore_type *lore_ptr)
{
    if (lore_ptr->a_ability_flags1 & (RF5_BO_ACID)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_ACID), _("アシッド・ボルト%s", "produce acid bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_GREEN;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_ELEC)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_ELEC), _("サンダー・ボルト%s", "produce lightning bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_BLUE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_FIRE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_FIRE), _("ファイア・ボルト%s", "produce fire bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_RED;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_COLD)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_COLD), _("アイス・ボルト%s", "produce frost bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_NETH)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_NETHER), _("地獄の矢%s", "produce nether bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_DARK;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_WATE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_WATER), _("ウォーター・ボルト%s", "produce water bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_BLUE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_MANA)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_MANA), _("魔力の矢%s", "produce mana bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_BLUE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_PLAS)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_PLASMA), _("プラズマ・ボルト%s", "produce plasma bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_L_RED;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BO_ICEE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_BOLT_ICE), _("極寒の矢%s", "produce ice bolts%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_WHITE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_MISSILE)) {
        set_damage(player_ptr, lore_ptr->r_idx, (MS_MAGIC_MISSILE), _("マジックミサイル%s", "produce magic missiles%s"), lore_ptr->tmp_msg[lore_ptr->vn]);
        lore_ptr->vp[lore_ptr->vn] = lore_ptr->tmp_msg[lore_ptr->vn];
        lore_ptr->color[lore_ptr->vn++] = TERM_SLATE;
    }
}

void set_status_types(lore_type *lore_ptr)
{
    if (lore_ptr->a_ability_flags1 & (RF5_SCARE)) {
        lore_ptr->vp[lore_ptr->vn] = _("恐怖", "terrify");
        lore_ptr->color[lore_ptr->vn++] = TERM_SLATE;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_BLIND)) {
        lore_ptr->vp[lore_ptr->vn] = _("目くらまし", "blind");
        lore_ptr->color[lore_ptr->vn++] = TERM_L_DARK;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_CONF)) {
        lore_ptr->vp[lore_ptr->vn] = _("混乱", "confuse");
        lore_ptr->color[lore_ptr->vn++] = TERM_L_UMBER;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_SLOW)) {
        lore_ptr->vp[lore_ptr->vn] = _("減速", "slow");
        lore_ptr->color[lore_ptr->vn++] = TERM_UMBER;
    }

    if (lore_ptr->a_ability_flags1 & (RF5_HOLD)) {
        lore_ptr->vp[lore_ptr->vn] = _("麻痺", "paralyze");
        lore_ptr->color[lore_ptr->vn++] = TERM_RED;
    }

    if (lore_ptr->a_ability_flags2 & (RF6_HASTE)) {
        lore_ptr->vp[lore_ptr->vn] = _("加速", "haste-self");
        lore_ptr->color[lore_ptr->vn++] = TERM_L_GREEN;
    }

    if (lore_ptr->a_ability_flags2 & (RF6_HEAL)) {
        lore_ptr->vp[lore_ptr->vn] = _("治癒", "heal-self");
        lore_ptr->color[lore_ptr->vn++] = TERM_WHITE;
    }

    if (lore_ptr->a_ability_flags2 & (RF6_INVULNER)) {
        lore_ptr->vp[lore_ptr->vn] = _("無敵化", "make invulnerable");
        lore_ptr->color[lore_ptr->vn++] = TERM_WHITE;
    }

    if (lore_ptr->flags4 & RF4_DISPEL) {
        lore_ptr->vp[lore_ptr->vn] = _("魔力消去", "dispel-magic");
        lore_ptr->color[lore_ptr->vn++] = TERM_L_WHITE;
    }
}
