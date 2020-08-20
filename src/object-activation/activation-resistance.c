#include "object-activation/activation-resistance.h"
#include "core/hp-mp-processor.h"
#include "spell-kind/spells-launcher.h"
#include "spell/spell-types.h"
#include "status/bad-status-setter.h"
#include "status/buff-setter.h"
#include "status/element-resistance.h"
#include "status/temporary-resistance.h"
#include "sv-definition/sv-ring-types.h"
#include "system/object-type-definition.h"
#include "target/target-getter.h"
#include "view/display-messages.h"

bool activate_resistance_elements(player_type *user_ptr)
{
    msg_print(_("�l�X�ȐF�ɋP���Ă���...", "It glows many colours..."));
    (void)set_oppose_acid(user_ptr, randint1(40) + 40, FALSE);
    (void)set_oppose_elec(user_ptr, randint1(40) + 40, FALSE);
    (void)set_oppose_fire(user_ptr, randint1(40) + 40, FALSE);
    (void)set_oppose_cold(user_ptr, randint1(40) + 40, FALSE);
    (void)set_oppose_pois(user_ptr, randint1(40) + 40, FALSE);
    return TRUE;
}

/*!
 * @brief �A�V�b�h�E�{�[��������A�X�Ɏ_�ϐ��𓾂�
 * @param user_ptr �v���[���[�ւ̎Q�ƃ|�C���^
 * @param o_ptr �����ΏۃA�C�e���ւ̎Q�ƃ|�C���^
 * @param name �A�C�e����
 * @return �{�[���𓖂Ă���Ȃ��TRUE
 */
bool activate_resistance_acid(player_type *user_ptr, object_type *o_ptr, concptr name)
{
    msg_format(_("%s�������P����...", "The %s grows black."), name);
    if ((o_ptr->tval != TV_RING) || (o_ptr->sval != SV_RING_ACID))
        return TRUE;

    DIRECTION dir;
    if (!get_aim_dir(user_ptr, &dir))
        return FALSE;

    (void)fire_ball(user_ptr, GF_ACID, dir, 100, 2);
    (void)set_oppose_acid(user_ptr, randint1(20) + 20, FALSE);
    return TRUE;
}

/*!
 * @brief �T���_�[�E�{�[��������A�X�ɓd���ϐ��𓾂�
 * @param user_ptr �v���[���[�ւ̎Q�ƃ|�C���^
 * @param o_ptr �����ΏۃA�C�e���ւ̎Q�ƃ|�C���^
 * @param name �A�C�e����
 * @return �{�[���𓖂Ă���Ȃ��TRUE
 */
bool activate_resistance_elec(player_type *user_ptr, object_type *o_ptr, concptr name)
{
    msg_format(_("%s�����P����...", "The %s grows blue."), name);
    if ((o_ptr->tval != TV_RING) || (o_ptr->sval != SV_RING_ELEC))
        return TRUE;

    DIRECTION dir;
    if (!get_aim_dir(user_ptr, &dir))
        return FALSE;

    (void)fire_ball(user_ptr, GF_ELEC, dir, 100, 2);
    (void)set_oppose_elec(user_ptr, randint1(20) + 20, FALSE);
    return TRUE;
}

/*!
 * @brief �t�@�C�A�E�{�[��������A�X�ɉΉ��ϐ��𓾂�
 * @param user_ptr �v���[���[�ւ̎Q�ƃ|�C���^
 * @param o_ptr �����ΏۃA�C�e���ւ̎Q�ƃ|�C���^
 * @param name �A�C�e����
 * @return �{�[���𓖂Ă���Ȃ��TRUE
 */
bool activate_resistance_fire(player_type *user_ptr, object_type *o_ptr, concptr name)
{
    msg_format(_("%s���Ԃ��P����...", "The %s grows red."), name);
    if ((o_ptr->tval != TV_RING) || (o_ptr->sval != SV_RING_FLAMES))
        return TRUE;

    DIRECTION dir;
    if (!get_aim_dir(user_ptr, &dir))
        return FALSE;

    (void)fire_ball(user_ptr, GF_FIRE, dir, 100, 2);
    (void)set_oppose_fire(user_ptr, randint1(20) + 20, FALSE);
    return TRUE;
}

/*!
 * @brief �A�C�X�E�{�[��������A�X�ɗ�C�ϐ��𓾂�
 * @param user_ptr �v���[���[�ւ̎Q�ƃ|�C���^
 * @param o_ptr �����ΏۃA�C�e���ւ̎Q�ƃ|�C���^
 * @param name �A�C�e����
 * @return �{�[���𓖂Ă���Ȃ��TRUE
 */
bool activate_resistance_cold(player_type *user_ptr, object_type *o_ptr, concptr name)
{
    msg_format(_("%s�������P����...", "The %s grows white."), name);
    if ((o_ptr->tval != TV_RING) || (o_ptr->sval != SV_RING_ICE))
        return TRUE;

    DIRECTION dir;
    if (!get_aim_dir(user_ptr, &dir))
        return FALSE;

    (void)fire_ball(user_ptr, GF_COLD, dir, 100, 2);
    (void)set_oppose_cold(user_ptr, randint1(20) + 20, FALSE);
    return TRUE;
}

/*!
 * todo �����ǉ����ʂ��~����
 * @brief �őϐ��𓾂�
 * @param user_ptr �v���[���[�ւ̎Q�ƃ|�C���^
 * @param name �A�C�e����
 * @return ���TRUE
 */
bool activate_resistance_pois(player_type *user_ptr, concptr name)
{
    msg_format(_("%s���΂ɋP����...", "The %s grows green."), name);
    (void)set_oppose_pois(user_ptr, randint1(20) + 20, FALSE);
    return TRUE;
}

bool activate_ultimate_resistance(player_type *user_ptr)
{
    TIME_EFFECT v = randint1(25) + 25;
    (void)set_afraid(user_ptr, 0);
    (void)set_hero(user_ptr, v, FALSE);
    (void)hp_player(user_ptr, 10);
    (void)set_blessed(user_ptr, v, FALSE);
    (void)set_oppose_acid(user_ptr, v, FALSE);
    (void)set_oppose_elec(user_ptr, v, FALSE);
    (void)set_oppose_fire(user_ptr, v, FALSE);
    (void)set_oppose_cold(user_ptr, v, FALSE);
    (void)set_oppose_pois(user_ptr, v, FALSE);
    (void)set_ultimate_res(user_ptr, v, FALSE);
    return TRUE;
}