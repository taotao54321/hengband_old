﻿#include "angband.h"
#include "trap.h"

static s16b normal_traps[MAX_NORMAL_TRAPS];


/*!
* @brief タグに従って、基本トラップテーブルを初期化する / Initialize arrays for normal traps
* @return なし
*/
void init_normal_traps(void)
{
	int cur_trap = 0;

	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_TRAPDOOR");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_PIT");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_SPIKED_PIT");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_POISON_PIT");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_TY_CURSE");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_TELEPORT");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_FIRE");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_ACID");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_SLOW");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_LOSE_STR");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_LOSE_DEX");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_LOSE_CON");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_BLIND");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_CONFUSE");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_POISON");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_SLEEP");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_TRAPS");
	normal_traps[cur_trap++] = f_tag_to_index_in_init("TRAP_ALARM");
}

/*!
* @brief 基本トラップをランダムに選択する /
* Get random trap
* @return 選択したトラップのID
* @details
* This routine should be redone to reflect trap "level".\n
* That is, it does not make sense to have spiked pits at 50 feet.\n
* Actually, it is not this routine, but the "trap instantiation"\n
* code, which should also check for "trap doors" on quest levels.\n
*/
FEAT_IDX choose_random_trap(void)
{
	FEAT_IDX feat;

	/* Pick a trap */
	while (1)
	{
		/* Hack -- pick a trap */
		feat = normal_traps[randint0(MAX_NORMAL_TRAPS)];

		/* Accept non-trapdoors */
		if (!have_flag(f_info[feat].flags, FF_MORE)) break;

		/* Hack -- no trap doors on special levels */
		if (p_ptr->inside_arena || quest_number(dun_level)) continue;

		/* Hack -- no trap doors on the deepest level */
		if (dun_level >= d_info[dungeon_type].maxdepth) continue;

		break;
	}

	return feat;
}

/*!
* @brief マスに存在するトラップを秘匿する /
* Disclose an invisible trap
* @param y 秘匿したいマスのY座標
* @param x 秘匿したいマスのX座標
* @return なし
*/
void disclose_grid(POSITION y, POSITION x)
{
	cave_type *c_ptr = &cave[y][x];

	if (cave_have_flag_grid(c_ptr, FF_SECRET))
	{
		/* No longer hidden */
		cave_alter_feat(y, x, FF_SECRET);
	}
	else if (c_ptr->mimic)
	{
		/* No longer hidden */
		c_ptr->mimic = 0;

		note_spot(y, x);

		/* Redraw */
		lite_spot(y, x);
	}
}

/*!
* @brief マスをトラップを配置する /
* The location must be a legal, naked, floor grid.
* @param y 配置したいマスのY座標
* @param x 配置したいマスのX座標
* @return
* Note that all traps start out as "invisible" and "untyped", and then\n
* when they are "discovered" (by detecting them or setting them off),\n
* the trap is "instantiated" as a visible, "typed", trap.\n
*/
void place_trap(POSITION y, POSITION x)
{
	cave_type *c_ptr = &cave[y][x];

	/* Paranoia -- verify location */
	if (!in_bounds(y, x)) return;

	/* Require empty, clean, floor grid */
	if (!cave_clean_bold(y, x)) return;

	/* Place an invisible trap */
	c_ptr->mimic = c_ptr->feat;
	c_ptr->feat = choose_random_trap();
}



/*!
* @brief プレイヤーへのトラップ命中判定 /
* Determine if a trap affects the player.
* @param power 基本回避難度
* @return トラップが命中した場合TRUEを返す。
* @details
* Always miss 5% of the time, Always hit 5% of the time.
* Otherwise, match trap power against player armor.
*/
static int check_hit(int power)
{
	int k;
	ARMOUR_CLASS ac;

	/* Percentile dice */
	k = randint0(100);

	/* Hack -- 5% hit, 5% miss */
	if (k < 10) return (k < 5);

	if (p_ptr->pseikaku == SEIKAKU_NAMAKE)
		if (one_in_(20)) return (TRUE);

	/* Paranoia -- No power */
	if (power <= 0) return (FALSE);

	/* Total armor */
	ac = p_ptr->ac + p_ptr->to_a;

	/* Power competes against Armor */
	if (randint1(power) > ((ac * 3) / 4)) return (TRUE);

	/* Assume miss */
	return (FALSE);
}


/*!
* @brief 落とし穴系トラップの判定とプレイヤーの被害処理
* @param trap_feat_type トラップの種別ID
* @return なし
*/
static void hit_trap_pit(int trap_feat_type)
{
	HIT_POINT dam;
	cptr trap_name = "";
	cptr spike_name = "";

	switch (trap_feat_type)
	{
	case TRAP_PIT:
		trap_name = _("落とし穴", "a pit trap");
		break;
	case TRAP_SPIKED_PIT:
		trap_name = _("スパイクが敷かれた落とし穴", "a spiked pit");
		spike_name = _("スパイク", "spikes");
		break;
	case TRAP_POISON_PIT:
		trap_name = _("スパイクが敷かれた落とし穴", "a spiked pit");
		spike_name = _("毒を塗られたスパイク", "poisonous spikes");
		break;
	default:
		return;
	}

	if (p_ptr->levitation)
	{
		msg_format(_("%sを飛び越えた。", "You fly over %s."), trap_name);
		return;
	}

	msg_format(_("%sに落ちてしまった！", "You have fallen into %s!"), trap_name);

	/* Base damage */
	dam = damroll(2, 6);

	/* Extra spike damage */
	if ((trap_feat_type == TRAP_SPIKED_PIT || trap_feat_type == TRAP_POISON_PIT) &&
		one_in_(2))
	{
		msg_format(_("%sが刺さった！", "You are impaled on %s!"), spike_name);

		dam = dam * 2;
		(void)set_cut(p_ptr->cut + randint1(dam));

		if (trap_feat_type == TRAP_POISON_PIT) {
			if (p_ptr->resist_pois || IS_OPPOSE_POIS())
			{
				msg_print(_("しかし毒の影響はなかった！", "The poison does not affect you!"));
			}
			else
			{
				dam = dam * 2;
				(void)set_poisoned(p_ptr->poisoned + randint1(dam));
			}
		}
	}

	take_hit(DAMAGE_NOESCAPE, dam, trap_name, -1);
}

/*!
* @brief ダーツ系トラップ（通常ダメージ）の判定とプレイヤーの被害処理
* @return ダーツが命中した場合TRUEを返す
*/
static bool hit_trap_dart(void)
{
	bool hit = FALSE;

	if (check_hit(125))
	{
		msg_print(_("小さなダーツが飛んできて刺さった！", "A small dart hits you!"));
		take_hit(DAMAGE_ATTACK, damroll(1, 4), _("ダーツの罠", "a dart trap"), -1);
		if (!CHECK_MULTISHADOW()) hit = TRUE;
	}
	else
	{
		msg_print(_("小さなダーツが飛んできた！が、運良く当たらなかった。", "A small dart barely misses you."));
	}

	return hit;
}

/*!
* @brief ダーツ系トラップ（通常ダメージ＋能力値減少）の判定とプレイヤーの被害処理
* @param stat 低下する能力値ID
* @return なし
*/
static void hit_trap_lose_stat(int stat)
{
	if (hit_trap_dart())
	{
		do_dec_stat(stat);
	}
}

/*!
* @brief ダーツ系トラップ（通常ダメージ＋減速）の判定とプレイヤーの被害処理
* @return なし
*/
static void hit_trap_slow(void)
{
	if (hit_trap_dart())
	{
		set_slow(p_ptr->slow + randint0(20) + 20, FALSE);
	}
}

/*!
* @brief ダーツ系トラップ（通常ダメージ＋状態異常）の判定とプレイヤーの被害処理
* @param trap_message メッセージの補完文字列
* @param resist 状態異常に抵抗する判定が出たならTRUE
* @param set_status 状態異常を指定する関数ポインタ
* @param turn 状態異常の追加ターン量
* @return なし
*/
static void hit_trap_set_abnormal_status(cptr trap_message, bool resist, bool(*set_status)(IDX), IDX turn_aux)
{
	msg_print(trap_message);
	if (!resist)
	{
		set_status(turn_aux);
	}
}

/*!
* @brief プレイヤーへのトラップ作動処理メインルーチン /
* Handle player hitting a real trap
* @param break_trap 作動後のトラップ破壊が確定しているならばTRUE
* @return なし
*/
void hit_trap(bool break_trap)
{
	int i, num, dam;
	POSITION x = p_ptr->x, y = p_ptr->y;

	/* Get the cave grid */
	cave_type *c_ptr = &cave[y][x];
	feature_type *f_ptr = &f_info[c_ptr->feat];
	int trap_feat_type = have_flag(f_ptr->flags, FF_TRAP) ? f_ptr->subtype : NOT_TRAP;
	cptr name = _("トラップ", "a trap");

	disturb(0, 1);

	cave_alter_feat(y, x, FF_HIT_TRAP);

	/* Analyze */
	switch (trap_feat_type)
	{
	case TRAP_TRAPDOOR:
	{
		if (p_ptr->levitation)
		{
			msg_print(_("落とし戸を飛び越えた。", "You fly over a trap door."));
		}
		else
		{
			msg_print(_("落とし戸に落ちた！", "You have fallen through a trap door!"));
			if ((p_ptr->pseikaku == SEIKAKU_COMBAT) || (inventory[INVEN_BOW].name1 == ART_CRIMSON))
				msg_print(_("くっそ～！", ""));

			sound(SOUND_FALL);
			dam = damroll(2, 8);
			name = _("落とし戸", "a trap door");

			take_hit(DAMAGE_NOESCAPE, dam, name, -1);

			/* Still alive and autosave enabled */
			if (autosave_l && (p_ptr->chp >= 0))
				do_cmd_save_game(TRUE);

			do_cmd_write_nikki(NIKKI_BUNSHOU, 0, _("落とし戸に落ちた", "You have fallen through a trap door!"));
			prepare_change_floor_mode(CFM_SAVE_FLOORS | CFM_DOWN | CFM_RAND_PLACE | CFM_RAND_CONNECT);

			/* Leaving */
			p_ptr->leaving = TRUE;
		}
		break;
	}

	case TRAP_PIT:
	case TRAP_SPIKED_PIT:
	case TRAP_POISON_PIT:
	{
		hit_trap_pit(trap_feat_type);
		break;
	}

	case TRAP_TY_CURSE:
	{
		msg_print(_("何かがピカッと光った！", "There is a flash of shimmering light!"));
		num = 2 + randint1(3);
		for (i = 0; i < num; i++)
		{
			(void)summon_specific(0, y, x, dun_level, 0, (PM_ALLOW_GROUP | PM_ALLOW_UNIQUE | PM_NO_PET));
		}

		if (dun_level > randint1(100)) /* No nasty effect for low levels */
		{
			bool stop_ty = FALSE;
			int count = 0;

			do
			{
				stop_ty = activate_ty_curse(stop_ty, &count);
			} while (one_in_(6));
		}
		break;
	}

	case TRAP_TELEPORT:
	{
		msg_print(_("テレポート・トラップにひっかかった！", "You hit a teleport trap!"));
		teleport_player(100, TELEPORT_PASSIVE);
		break;
	}

	case TRAP_FIRE:
	{
		msg_print(_("炎に包まれた！", "You are enveloped in flames!"));
		dam = damroll(4, 6);
		(void)fire_dam(dam, _("炎のトラップ", "a fire trap"), -1, FALSE);
		break;
	}

	case TRAP_ACID:
	{
		msg_print(_("酸が吹きかけられた！", "You are splashed with acid!"));
		dam = damroll(4, 6);
		(void)acid_dam(dam, _("酸のトラップ", "an acid trap"), -1, FALSE);
		break;
	}

	case TRAP_SLOW:
	{
		hit_trap_slow();
		break;
	}

	case TRAP_LOSE_STR:
	{
		hit_trap_lose_stat(A_STR);
		break;
	}

	case TRAP_LOSE_DEX:
	{
		hit_trap_lose_stat(A_DEX);
		break;
	}

	case TRAP_LOSE_CON:
	{
		hit_trap_lose_stat(A_CON);
		break;
	}

	case TRAP_BLIND:
	{
		hit_trap_set_abnormal_status(
			_("黒いガスに包み込まれた！", "A black gas surrounds you!"),
			p_ptr->resist_blind,
			set_blind, p_ptr->blind + (TIME_EFFECT)randint0(50) + 25);
		break;
	}

	case TRAP_CONFUSE:
	{
		hit_trap_set_abnormal_status(
			_("きらめくガスに包み込まれた！", "A gas of scintillating colors surrounds you!"),
			p_ptr->resist_conf,
			set_confused, p_ptr->confused + (TIME_EFFECT)randint0(20) + 10);
		break;
	}

	case TRAP_POISON:
	{
		hit_trap_set_abnormal_status(
			_("刺激的な緑色のガスに包み込まれた！", "A pungent green gas surrounds you!"),
			p_ptr->resist_pois || IS_OPPOSE_POIS(),
			set_poisoned, p_ptr->poisoned + (TIME_EFFECT)randint0(20) + 10);
		break;
	}

	case TRAP_SLEEP:
	{
		msg_print(_("奇妙な白い霧に包まれた！", "A strange white mist surrounds you!"));
		if (!p_ptr->free_act)
		{
			msg_print(_("あなたは眠りに就いた。", "You fall asleep."));

			if (ironman_nightmare)
			{
				msg_print(_("身の毛もよだつ光景が頭に浮かんだ。", "A horrible vision enters your mind."));

				/* Have some nightmares */
				sanity_blast(NULL, FALSE);

			}
			(void)set_paralyzed(p_ptr->paralyzed + randint0(10) + 5);
		}
		break;
	}

	case TRAP_TRAPS:
	{
		msg_print(_("まばゆい閃光が走った！", "There is a bright flash of light!"));
		/* Make some new traps */
		project(0, 1, y, x, 0, GF_MAKE_TRAP, PROJECT_HIDE | PROJECT_JUMP | PROJECT_GRID, -1);

		break;
	}

	case TRAP_ALARM:
	{
		msg_print(_("けたたましい音が鳴り響いた！", "An alarm sounds!"));

		aggravate_monsters(0);

		break;
	}

	case TRAP_OPEN:
	{
		msg_print(_("大音響と共にまわりの壁が崩れた！", "Suddenly, surrounding walls are opened!"));
		(void)project(0, 3, y, x, 0, GF_DISINTEGRATE, PROJECT_GRID | PROJECT_HIDE, -1);
		(void)project(0, 3, y, x - 4, 0, GF_DISINTEGRATE, PROJECT_GRID | PROJECT_HIDE, -1);
		(void)project(0, 3, y, x + 4, 0, GF_DISINTEGRATE, PROJECT_GRID | PROJECT_HIDE, -1);
		aggravate_monsters(0);

		break;
	}

	case TRAP_ARMAGEDDON:
	{
		static int levs[10] = { 0, 0, 20, 10, 5, 3, 2, 1, 1, 1 };
		int evil_idx = 0, good_idx = 0;

		DEPTH lev;
		msg_print(_("突然天界の戦争に巻き込まれた！", "Suddenly, you are surrounded by immotal beings!"));

		/* Summon Demons and Angels */
		for (lev = dun_level; lev >= 20; lev -= 1 + lev / 16)
		{
			num = levs[MIN(lev / 10, 9)];
			for (i = 0; i < num; i++)
			{
				POSITION x1 = rand_spread(x, 7);
				POSITION y1 = rand_spread(y, 5);

				/* Skip illegal grids */
				if (!in_bounds(y1, x1)) continue;

				/* Require line of projection */
				if (!projectable(p_ptr->y, p_ptr->x, y1, x1)) continue;

				if (summon_specific(0, y1, x1, lev, SUMMON_ARMAGE_EVIL, (PM_NO_PET)))
					evil_idx = hack_m_idx_ii;

				if (summon_specific(0, y1, x1, lev, SUMMON_ARMAGE_GOOD, (PM_NO_PET)))
				{
					good_idx = hack_m_idx_ii;
				}

				/* Let them fight each other */
				if (evil_idx && good_idx)
				{
					monster_type *evil_ptr = &m_list[evil_idx];
					monster_type *good_ptr = &m_list[good_idx];
					evil_ptr->target_y = good_ptr->fy;
					evil_ptr->target_x = good_ptr->fx;
					good_ptr->target_y = evil_ptr->fy;
					good_ptr->target_x = evil_ptr->fx;
				}
			}
		}
		break;
	}

	case TRAP_PIRANHA:
	{
		msg_print(_("突然壁から水が溢れ出した！ピラニアがいる！", "Suddenly, the room is filled with water with piranhas!"));

		/* Water fills room */
		fire_ball_hide(GF_WATER_FLOW, 0, 1, 10);

		/* Summon Piranhas */
		num = 1 + dun_level / 20;
		for (i = 0; i < num; i++)
		{
			(void)summon_specific(0, y, x, dun_level, SUMMON_PIRANHAS, (PM_ALLOW_GROUP | PM_NO_PET));
		}
		break;
	}
	}

	if (break_trap && is_trap(c_ptr->feat))
	{
		cave_alter_feat(y, x, FF_DISARM);
		msg_print(_("トラップを粉砕した。", "You destroyed the trap."));
	}
}
