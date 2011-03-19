/* player/fake.c - Code to generate fake players for power ratings */

#include "player/types.h"
#include "player/player.h"
#include "player/fake.h"

/**
 * Populate stats for fake players
 *
 * Should be level- or depth-dependent. For now, just constant.
 */
static void fake_player_stats(player_type *fp_ptr)
{
	int i;

	for (i = 0; i < A_MAX; i++)
	{
		fp_ptr->stat_birth[i] = 13;
		fp_ptr->stat_cur[i]   = 13;
		fp_ptr->stat_max[i]   = 13;
	}
}

/**
 * Populate inventory for fake players
 *
 * Should be level- or depth-dependent. For now, just empty.
 */
static void fake_player_inventory(player_type *fp_ptr)
{
	fp_ptr->inventory = C_ZNEW(ALL_INVEN_TOTAL, object_type);
}

/**
 * Learn spells for fake players
 *
 * Should be level- or depth-dependent. For now, all unlearned.
 */
static void fake_player_spells(player_type *fp_ptr)
{
	int i;

	for (i = 0; i < PY_MAX_SPELLS; i++)
		fp_ptr->spell_order[i] = 99;
}

static player_type *make_fake_player(int lev, const player_race *race, const player_class *class)
{
	player_type *fp_ptr = mem_zalloc(sizeof(fp_ptr));

	fp_ptr->race  = race;
	fp_ptr->class = class;
	fp_ptr->psex  = SEX_FEMALE;
	fp_ptr->lev   = fp_ptr->max_lev = lev;

	fake_player_stats(fp_ptr);
	fake_player_inventory(fp_ptr);
	fake_player_spells(fp_ptr);

	calc_bonuses(fp_ptr->inventory, &fp_ptr->state, FALSE);
	return fp_ptr;	
}

static void free_fake_player(player_type *fp_ptr)
{
	if (fp_ptr->inventory)
		mem_free(fp_ptr->inventory);

	mem_free(fp_ptr);
}

/* Sample interface function
 * s32b monster_max_dmg_aux(int lev, const player_race *race, const player_class *class)
 * {
 * 	s32b dmg;
 *      struct player_type *fp_ptr = make_fake_player(lev, race, class); 
 *
 *      dmg = monster_max_dmg(fp_ptr);
 * 	free_fake_player(fp_ptr);
 * 	return dmg;
 * }
 */
