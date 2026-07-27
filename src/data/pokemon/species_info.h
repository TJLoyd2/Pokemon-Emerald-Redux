#include "constants/abilities.h"
#include "constants/teaching_types.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }
#define CONDITIONS(...) ((const struct EvolutionParam[]) { __VA_ARGS__, {CONDITIONS_END} })

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_PORYGON,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    /* You may add any custom species below this point based on the following structure: */
	//Convergent Species Kanto
	[SPECIES_FOGGING] =
    {
        .baseHP        = 60,
        .baseAttack    = 45,
        .baseDefense   = 55,
        .baseSpeed     = 65,
        .baseSpAttack  = 60,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_WATER, TYPE_FLYING),
        .catchRate = 190,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 68 : 114,
        .evYield_Defense = 1,
        .itemRare = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
    #if P_UPDATED_ABILITIES >= GEN_8
        .abilities = { ABILITY_WIND_RIDER, ABILITY_WATER_ABSORB, ABILITY_DRIZZLE },
    #else
        .abilities = { ABILITY_WATER_ABSORB, ABILITY_NONE, ABILITY_NONE },
    #endif
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Fogging"),
        .cryId = CRY_KOFFING,
        .natDexNum = NATIONAL_DEX_KOFFING,
        .categoryName = _("Rain Cloud"),
        .height = 6,
        .weight = 10,
        .description = COMPOUND_STRING(
            "Although it looks like KOFFING\n"
            "its body is pure water vapor. It\n"
            "floats lazily through coastal skies,\n"
            "bringing refreshing rain showers."),
        .pokemonScale = 369,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fogging,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 8 : 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_IN_STAGES,
        .enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 14,
        .backPic = gMonBackPic_Fogging,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 3,
        .backAnimId = BACK_ANIM_SHRINK_GROW,
        .palette = gMonPalette_Fogging,
        .shinyPalette = gMonShinyPalette_Fogging,
        .iconSprite = gMonIcon_Koffing,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 15, SHADOW_SIZE_S)
        FOOTPRINT(Koffing)
        OVERWORLD(
            sPicTable_Koffing,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Koffing,
            gShinyOverworldPalette_Koffing
        )
        .levelUpLearnset = sFoggingLevelUpLearnset,
        .teachableLearnset = sKoffingTeachableLearnset,
        .eggMoveLearnset = sKoffingEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_BREEZING}),
    },

    [SPECIES_BREEZING] =
    {
        .baseHP        = 120,
        .baseAttack    = 70,
        .baseDefense   = 60,
        .baseSpeed     = 85,
        .baseSpAttack  = 95,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_WATER, TYPE_FLYING),
        .catchRate = 60,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 172 : 173,
        .evYield_Defense = 2,
        .itemRare = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
    #if P_UPDATED_ABILITIES >= GEN_8
        .abilities = { ABILITY_LIGHTNING_ROD, ABILITY_WATER_ABSORB, ABILITY_DRIZZLE },
    #else
        .abilities = { ABILITY_LIGHTNING_ROD, ABILITY_WATER_ABSORB, ABILITY_NONE },
    #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = TRUE,
        .speciesName = _("Breezing"),
        .cryId = CRY_WEEZING,
        .natDexNum = NATIONAL_DEX_WEEZING,
        .categoryName = _("Rain Cloud"),
        .height = 12,
        .weight = 95,
        .description = COMPOUND_STRING(
            "It forms when two weather fronts\n"
            "collide. The smaller cloud head is\n"
            "calm, while the larger head builds\n"
            "up intense barometric pressure."),
        .pokemonScale = 305,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Breezing,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 2 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_CIRCLE_INTO_BG,
        .enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 6 : 9,
        .backPic = gMonBackPic_Breezing,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 6 : 9,
        .backAnimId = BACK_ANIM_H_STRETCH,
        .palette = gMonPalette_Breezing,
        .shinyPalette = gMonShinyPalette_Breezing,
        .iconSprite = gMonIcon_Breezing,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 19, SHADOW_SIZE_M)
        FOOTPRINT(Breezing)
        OVERWORLD(
            sPicTable_Weezing,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following_Asym,
            gOverworldPalette_Weezing,
            gShinyOverworldPalette_Weezing
        )
        .levelUpLearnset = sBreezingLevelUpLearnset,
        .teachableLearnset = sWeezingTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 50, SPECIES_STORMING}),
    },
	
	[SPECIES_STORMING] =
    {
        .baseHP        = 135,
        .baseAttack    = 70,
        .baseDefense   = 65,
        .baseSpeed     = 80,
        .baseSpAttack  = 105,
        .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_WATER, TYPE_FLYING),
        .catchRate = 60,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 172 : 214,
        .evYield_Defense = 3,
        .itemRare = ITEM_MYSTIC_WATER,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
    #if P_UPDATED_ABILITIES >= GEN_8
        .abilities = { ABILITY_LIGHTNING_ROD, ABILITY_WATER_ABSORB, ABILITY_DRIZZLE },
    #else
        .abilities = { ABILITY_LIGHTNING_ROD, ABILITY_WATER_ABSORB, ABILITY_NONE },
    #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = TRUE,
        .speciesName = _("Storming"),
        .cryId = CRY_WEEZING,
        .natDexNum = NATIONAL_DEX_WEEZING,
        .categoryName = _("Rain Cloud"),
        .height = 15,
        .weight = 95,
        .description = COMPOUND_STRING(
            "Born from extreme atmospheric chaos,\n"
            "the violent friction between its three\n"
            "heads releases constant lightning.\n"
            "It can trigger massive flash floods."),
        .pokemonScale = 305,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Storming,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 2 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_VIBRATE,
        .enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 6 : 3,
        .backPic = gMonBackPic_Storming,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 6 : 9,
        .backAnimId = BACK_ANIM_GROW,
        .palette = gMonPalette_Storming,
        .shinyPalette = gMonShinyPalette_Storming,
        .iconSprite = gMonIcon_Storming,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 14, SHADOW_SIZE_L)
        FOOTPRINT(Weezing)
        OVERWORLD(
            sPicTable_Weezing,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following_Asym,
            gOverworldPalette_Weezing,
            gShinyOverworldPalette_Weezing
        )
        .levelUpLearnset = sStormingLevelUpLearnset,
        .teachableLearnset = sWeezingTeachableLearnset,
    },
	
	[SPECIES_MERRYKARP] =
    {
        .baseHP        = 40,
        .baseAttack    = 15,
        .baseDefense   = 15,
        .baseSpeed     = 60,
        .baseSpAttack  = 55,
        .baseSpDefense = 20,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FAIRY),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 40 : 20,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_WIND_RIDER, ABILITY_BLAZE, ABILITY_SOUNDPROOF },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Merrykarp"),
        .cryId = CRY_MAGIKARP,
        .natDexNum = NATIONAL_DEX_MAGIKARP,
        .categoryName = _("Lantern"),
        .height = 9,
        .weight = 100,
        .description = COMPOUND_STRING(
            "It loves crowds and rides on warm\n"
            "updrafts above busy town squares.\n"
            "It bobbles playfully through the air\n"
            "to entertain passing children."),
        .pokemonScale = 310,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Merrykarp,
        .frontPicSize = MON_COORDS_SIZE(48, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 6 : 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_BOUNCE_ROTATE_TO_SIDES,
		.enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 6 : 3,
        .backPic = gMonBackPic_Merrykarp,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 0,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_LARGE,
        .palette = gMonPalette_Merrykarp,
        .shinyPalette = gMonShinyPalette_Merrykarp,
        .iconSprite = gMonIcon_Merrykarp,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 9, SHADOW_SIZE_M)
        FOOTPRINT(Magikarp)
        OVERWORLD(
            sPicTable_Magikarp,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SPOT,
            sAnimTable_Following,
            gOverworldPalette_Magikarp,
            gShinyOverworldPalette_Magikarp
        )
        .teachingType = TM_ILLITERATE,
        .levelUpLearnset = sMerrykarpLevelUpLearnset,
        .teachableLearnset = sMagikarpTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_GYAREVELRY}),
    },

    [SPECIES_GYAREVELRY] =
    {
        .baseHP        = 110,
        .baseAttack    = 60,
        .baseDefense   = 70,
        .baseSpeed     = 70,
        .baseSpAttack  = 112,
        .baseSpDefense = 118,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 189 : 214,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 5,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_2, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_DANCER, ABILITY_BLAZE, ABILITY_SOUNDPROOF },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Gyarevelry"),
        .cryId = CRY_GYARADOS,
        .natDexNum = NATIONAL_DEX_GYARADOS,
        .categoryName = _("Grand Parade"),
        .height = 65,
        .weight = 2350,
        .description = COMPOUND_STRING(
            "It rides on festive cheer and warm\n"
            "winds, weaving through the sky like\n"
            "a massive kite. A town it visits is said\n"
            "to have a prosperous year free of hardship."),
        .pokemonScale = 256,
        .pokemonOffset = 6,
        .trainerScale = 481,
        .trainerOffset = 13,
        .frontPic = gMonFrontPic_Gyarevelry,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 8 : 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL,
		.enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 5,
        .backPic = gMonBackPic_Gyarevelry,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 0 : 0,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_Gyarevelry,
        .shinyPalette = gMonShinyPalette_Gyarevelry,
        .iconSprite = gMonIcon_Gyarevelry,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 12, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Gyarados)
        OVERWORLD(
            sPicTable_Gyarados,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_Gyarados,
            gShinyOverworldPalette_Gyarados
        )
        .levelUpLearnset = sGyarevelryLevelUpLearnset,
        .teachableLearnset = sGyaradosTeachableLearnset,
    },
	
	//Convergent Species Johto
    [SPECIES_MARBEEP] =
    {
        .baseHP        = 70,
        .baseAttack    = 40,
        .baseDefense   = 45,
        .baseSpeed     = 30,
        .baseSpAttack  = 65,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_BUG),
        .catchRate = 235,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 56 : 59,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG, EGG_GROUP_FIELD),
        .abilities = { ABILITY_HONEY_GATHER, ABILITY_COMPOUND_EYES, ABILITY_GOOEY },
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = TRUE,
        .speciesName = _("Marbeep"),
        .cryId = CRY_MAREEP,
        .natDexNum = NATIONAL_DEX_MARBEEP,
        .categoryName = _("Bee"),
        .height = 6,
        .weight = 78,
        .description = COMPOUND_STRING(
            "Its incredibly fluffy body is covered\n"
            "in sticky, sweet-smelling fleece.\n"
            "It rubs against flowers to collect\n"
			"pollen, which it carries back home."),
        .pokemonScale = 379,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Marbeep,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 40) : MON_COORDS_SIZE(40, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 16 : 12,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 10),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 20),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
		.enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 11,
        .backPic = gMonBackPic_Marbeep,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 6,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        .palette = gMonPalette_Marbeep,
        .shinyPalette = gMonShinyPalette_Marbeep,
        .iconSprite = gMonIcon_Marbeep,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(1, 8, SHADOW_SIZE_M)
        FOOTPRINT(Marbeep)
        OVERWORLD(
            sPicTable_Mareep,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Mareep,
            gShinyOverworldPalette_Mareep
        )
        .levelUpLearnset = sMarbeepLevelUpLearnset,
        .teachableLearnset = sMareepTeachableLearnset,
        .eggMoveLearnset = sMareepEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 15, SPECIES_FLUFFBEE}),
    },

    [SPECIES_FLUFFBEE] =
    {
        .baseHP        = 85,
        .baseAttack    = 55,
        .baseDefense   = 60,
        .baseSpeed     = 40,
        .baseSpAttack  = 80,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_BUG),
        .catchRate = 120,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 128 : 117,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_FIELD),
        .abilities = { ABILITY_HONEY_GATHER, ABILITY_COMPOUND_EYES, ABILITY_GOOEY },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Fluffbee"),
        .cryId = CRY_FLAAFFY,
        .natDexNum = NATIONAL_DEX_FLAAFFY,
        .categoryName = _("Bee"),
        .height = 8,
        .weight = 133,
        .description = COMPOUND_STRING(
            "As it flies, its large translucent\n"
            "wings vibrate fast enough to cause\n"
            "its fluffy wool to crackle. It fends\n"
            "off threats with a deafening buzz."),
        .pokemonScale = 372,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fluffbee,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 48) : MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 10 : 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_JUMPS_BIG : ANIM_V_STRETCH,
		.enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 3,
        .backPic = gMonBackPic_Fluffbee,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 7,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Fluffbee,
        .shinyPalette = gMonShinyPalette_Fluffbee,
        .iconSprite = gMonIcon_Fluffbee,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 8, SHADOW_SIZE_M)
        FOOTPRINT(Flaaffy)
        OVERWORLD(
            sPicTable_Flaaffy,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Flaaffy,
            gShinyOverworldPalette_Flaaffy
        )
        .levelUpLearnset = sFlaaffyLevelUpLearnset,
        .teachableLearnset = sFlaaffyTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_AMPHYBUZZ}),
    },

    [SPECIES_AMPHYBUZZ] =
    {
        .baseHP        = 110,
        .baseAttack    = 75,
        .baseDefense   = 90,
        .baseSpeed     = 50,
        .baseSpAttack  = 115,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_BUG, TYPE_FAIRY),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 255,
    #elif P_UPDATED_EXP_YIELDS >= GEN_6
        .expYield = 230,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 225,
    #else
        .expYield = 194,
    #endif
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_FIELD),
        .abilities = { ABILITY_HONEY_GATHER, ABILITY_COMPOUND_EYES, ABILITY_GOOEY },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Amphybuzz"),
        .cryId = CRY_AMPHAROS,
        .natDexNum = NATIONAL_DEX_AMPHAROS,
        .categoryName = _("Bumblebee"),
        .height = 14,
        .weight = 615,
        .description = COMPOUND_STRING(
            "Its wings shimmer with fairy dust\n"
            "as it flies high above the trees.\n"
            "It guides lost travelers out of deep\n"
            "forests using a warm, golden glow."),
        .pokemonScale = 256,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Amphybuzz,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(56, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_STRETCH,
        .frontAnimDelay = 10,
		.enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 7,
        .backPic = gMonBackPic_Amphybuzz,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 64) : MON_COORDS_SIZE(56, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 3,
        .backAnimId = BACK_ANIM_H_SPRING,
        .palette = gMonPalette_Amphybuzz,
        .shinyPalette = gMonShinyPalette_Amphybuzz,
        .iconSprite = gMonIcon_Ampharos,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 19, SHADOW_SIZE_M)
        FOOTPRINT(Ampharos)
        OVERWORLD(
            sPicTable_Ampharos,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Ampharos,
            gShinyOverworldPalette_Ampharos
        )
        .levelUpLearnset = sAmphybuzzLevelUpLearnset,
        .teachableLearnset = sAmpharosTeachableLearnset,
    },
	
	[SPECIES_SHRUBMA] =
    {
        .baseHP        = 50,
        .baseAttack    = 40,
        .baseDefense   = 50,
        .baseSpeed     = 15,
        .baseSpAttack  = 75,
        .baseSpDefense = 20,
        .types = MON_TYPES(TYPE_GRASS),
        .catchRate = 190,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 50 : 78,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_SIMPLE, ABILITY_NATURAL_CURE, ABILITY_SHELL_ARMOR },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Shrubma"),
        .cryId = CRY_SLUGMA,
        .natDexNum = NATIONAL_DEX_SLUGMA,
        .categoryName = _("Shrub"),
        .height = 7,
        .weight = 350,
        .description = COMPOUND_STRING(
           "When threatened, it tucks its head\n"
           "in to mimic a garden shrub. It feeds\n"
           "on rich soil, and its flowers wilt\n"
           "if it runs low on nutrients."),
        .pokemonScale = 329,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Shrubma,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 40) : MON_COORDS_SIZE(32, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_STRETCH,
        .backPic = gMonBackPic_Shrubma,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 8 : 0,
        .backAnimId = BACK_ANIM_H_STRETCH,
        .palette = gMonPalette_Shrubma,
        .shinyPalette = gMonShinyPalette_Shrubma,
        .iconSprite = gMonIcon_Shrubma,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(0, 0, SHADOW_SIZE_S)
        FOOTPRINT(Slugma)
        OVERWORLD(
            sPicTable_Slugma,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_Slugma,
            gShinyOverworldPalette_Slugma
        )
        .levelUpLearnset = sShrubmaLevelUpLearnset,
        .teachableLearnset = sSlugmaTeachableLearnset,
        .eggMoveLearnset = sSlugmaEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 23, SPECIES_ARCHCARGO}),
    },

    [SPECIES_ARCHCARGO] =
    {
        .baseHP        = 70,
        .baseAttack    = 50,
        .baseDefense   = 140,
        .baseSpeed     = 25,
        .baseSpAttack  = 100,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ROCK),
        .catchRate = 75,
    #if P_UPDATED_EXP_YIELDS >= GEN_7
        .expYield = 151,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 144,
    #else
        .expYield = 154,
    #endif
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_SIMPLE, ABILITY_NATURAL_CURE, ABILITY_SHELL_ARMOR },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("Archcargo"),
        .cryId = CRY_MAGCARGO,
        .natDexNum = NATIONAL_DEX_MAGCARGO,
        .categoryName = _("Shrub"),
        .height = 8,
        .weight = 550,
        .description = COMPOUND_STRING(
            "Its stony shell is incredibly heavy.\n"
            "The ancient carvings on its head\n"
            "absorb minerals from old ruins to\n"
            "help its vibrant flora constantly bloom."),
        .pokemonScale = 332,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Archcargo,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 56) : MON_COORDS_SIZE(56, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_STRETCH,
        .backPic = gMonBackPic_Archcargo,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 0,
        .backAnimId = BACK_ANIM_H_STRETCH,
        .palette = gMonPalette_Archcargo,
        .shinyPalette = gMonShinyPalette_Archcargo,
        .iconSprite = gMonIcon_Archcargo,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 5, SHADOW_SIZE_M)
        FOOTPRINT(Magcargo)
        OVERWORLD(
            sPicTable_Magcargo,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following_Asym,
            gOverworldPalette_Magcargo,
            gShinyOverworldPalette_Magcargo
        )
        .levelUpLearnset = sArchcargoLevelUpLearnset,
        .teachableLearnset = sMagcargoTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 45, SPECIES_ESCARGOLITHE}),
    },
	
	[SPECIES_ESCARGOLITHE] =
    {
        .baseHP        = 100,
        .baseAttack    = 50,
        .baseDefense   = 150,
        .baseSpeed     = 30,
        .baseSpAttack  = 100,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ROCK),
        .catchRate = 75,
    #if P_UPDATED_EXP_YIELDS >= GEN_7
        .expYield = 151,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 144,
    #else
        .expYield = 154,
    #endif
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_AMORPHOUS),
        .abilities = { ABILITY_SIMPLE, ABILITY_NATURAL_CURE, ABILITY_SHELL_ARMOR },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("Escargolithe"),
        .cryId = CRY_MAGCARGO,
        .natDexNum = NATIONAL_DEX_MAGCARGO,
        .categoryName = _("Lava"),
        .height = 8,
        .weight = 550,
        .description = COMPOUND_STRING(
           "A walking ancient city, its massive\n"
            "shell houses entire ecosystems of\n"
            "small bug POKéMON. It remains totally\n"
            "motionless for decades at a time."),
        .pokemonScale = 332,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Escargolithe,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 56) : MON_COORDS_SIZE(56, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_SHRINK_GROW_VIBRATE,
        .backPic = gMonBackPic_Escargolithe,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 0,
        .backAnimId = BACK_ANIM_H_STRETCH,
        .palette = gMonPalette_Escargolithe,
        .shinyPalette = gMonShinyPalette_Escargolithe,
        .iconSprite = gMonIcon_Escargolithe,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 5, SHADOW_SIZE_M)
        FOOTPRINT(Magcargo)
        OVERWORLD(
            sPicTable_Magcargo,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following_Asym,
            gOverworldPalette_Magcargo,
            gShinyOverworldPalette_Magcargo
        )
        .levelUpLearnset = sEscargolitheLevelUpLearnset,
        .teachableLearnset = sMagcargoTeachableLearnset,
    },
	
	//Convergent Species Hoenn
	[SPECIES_CORALTS] =
    {
        .baseHP        = 42,
        .baseAttack    = 27,
        .baseDefense   = 27,
        .baseSpeed     = 48,
        .baseSpAttack  = 57,
        .baseSpDefense = 32,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 235,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 40 : 70,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = RALTS_FAMILY_EGG_GROUPS,
        .abilities = { ABILITY_WATER_VEIL, ABILITY_NATURAL_CURE, ABILITY_LIQUID_OOZE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Coralts"),
        .cryId = CRY_RALTS,
        .natDexNum = NATIONAL_DEX_RALTS,
        .categoryName = _("Jellyfish"),
        .height = 4,
        .weight = 66,
        .description = COMPOUND_STRING(
            "It uses the coral horn on its head\n"
            "to sense changes in water currents.\n"
            "If it feels a trainer's kindness,\n"
            "it will swim close and dance playfully."),
        .pokemonScale = 457,
        .pokemonOffset = -3,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Coralts,
        .frontPicSize = MON_COORDS_SIZE(24, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 15 : 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
		.enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 6,
        .backPic = gMonBackPic_Coralts,
        .backPicSize = MON_COORDS_SIZE(32, 40),
        .backPicYOffset = 13,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Coralts,
        .shinyPalette = gMonShinyPalette_Coralts,
        .iconSprite = gMonIcon_Ralts,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(0, 4, SHADOW_SIZE_S)
        FOOTPRINT(Ralts)
        OVERWORLD(
            sPicTable_Ralts,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Ralts,
            gShinyOverworldPalette_Ralts
        )
        .levelUpLearnset = sCoraltsLevelUpLearnset,
        .teachableLearnset = sRaltsTeachableLearnset,
        .eggMoveLearnset = sRaltsEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_MARILIA}),
    },

    [SPECIES_MARILIA] =
    {
        .baseHP        = 58,
        .baseAttack    = 36,
        .baseDefense   = 37,
        .baseSpeed     = 74,
        .baseSpAttack  = 77,
        .baseSpDefense = 49,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 120,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 97 : 140,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = RALTS_FAMILY_EGG_GROUPS,
        .abilities = { ABILITY_WATER_VEIL, ABILITY_WATER_ABSORB, ABILITY_STATIC },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Marilia"),
        .cryId = CRY_KIRLIA,
        .natDexNum = NATIONAL_DEX_KIRLIA,
        .categoryName = _("Jellyfish"),
        .height = 8,
        .weight = 202,
        .description = COMPOUND_STRING(
            "It dances gracefully through deep\n"
            "ocean currents. The frills around\n"
            "its waist catch the water, letting\n"
            "it drift along like a jellyfish."),
        .pokemonScale = 354,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Marilia,
        .frontPicSize = MON_COORDS_SIZE(32, 56),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Marilia,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 56) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Marilia,
        .shinyPalette = gMonShinyPalette_Marilia,
        .iconSprite = gMonIcon_Kirlia,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(-2, 7, SHADOW_SIZE_S)
        FOOTPRINT(Kirlia)
        OVERWORLD(
            sPicTable_Kirlia,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Kirlia,
            gShinyOverworldPalette_Kirlia
        )
        .levelUpLearnset = sMariliaLevelUpLearnset,
        .teachableLearnset = sKirliaTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_SIRENVOIR}
                            #if P_GEN_4_CROSS_EVOS
                                ,{EVO_ITEM, ITEM_WATER_STONE, SPECIES_RIPPLADE}
                            #endif
                            ),
    },

    [SPECIES_SIRENVOIR] =
    {
        .baseHP        = 75,
        .baseAttack    = 125,
        .baseDefense   = 78,
        .baseSpeed     = 105,
        .baseSpAttack  = 85,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_WATER, TYPE_DARK),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 259,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 233,
    #else
        .expYield = 208,
    #endif
        .evYield_SpAttack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = RALTS_FAMILY_EGG_GROUPS,
        .abilities = { ABILITY_WATER_VEIL, ABILITY_MOXIE, ABILITY_LONG_REACH },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Sirenvoir"),
        .cryId = CRY_GARDEVOIR,
        .natDexNum = NATIONAL_DEX_GARDEVOIR,
        .categoryName = _("Siren"),
        .height = 16,
        .weight = 484,
        .description = COMPOUND_STRING(
            "It stalks the pitch-black depths of\n"
            "the ocean. It uses the glowing fins\n"
            "on its head to blind opponents before\n"
            "dragging them down into the abyss."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Sirenvoir,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_SQUISH_AND_BOUNCE : ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .backPic = gMonBackPic_Sirenvoir,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 6,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Sirenvoir,
        .shinyPalette = gMonShinyPalette_Sirenvoir,
        .iconSprite = gMonIcon_Gardevoir,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 14, SHADOW_SIZE_L)
        FOOTPRINT(Gardevoir)
        OVERWORLD(
            sPicTable_Gardevoir,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Gardevoir,
            gShinyOverworldPalette_Gardevoir
        )
        .levelUpLearnset = sSirenvoirLevelUpLearnset,
        .teachableLearnset = sGardevoirTeachableLearnset,
    },

    [SPECIES_RIPPLADE] =
    {
        .baseHP        = 105,
        .baseAttack    = 75,
        .baseDefense   = 78,
        .baseSpeed     = 65,
        .baseSpAttack  = 85,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_WATER, TYPE_FAIRY),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 259,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 233,
    #else
        .expYield = 208,
    #endif
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = RALTS_FAMILY_EGG_GROUPS,
    #if P_UPDATED_ABILITIES >= GEN_9
        .abilities = { ABILITY_STEADFAST, ABILITY_SHARPNESS, ABILITY_JUSTIFIED },
    #else
        .abilities = { ABILITY_STEADFAST, ABILITY_NONE, ABILITY_JUSTIFIED },
    #endif
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Ripplade"),
        .cryId = CRY_GALLADE,
        .natDexNum = NATIONAL_DEX_GALLADE,
        .categoryName = _("Blade"),
        .height = 16,
        .weight = 520,
        .description = COMPOUND_STRING(
            "A noble protector of the sea, it\n"
            "fights to defend weak POKéMON.\n"
            "Its fluid blade strikes create dazzling\n"
            "ripples that blind its foes."),
        .pokemonScale = 259,
        .pokemonOffset = 1,
        .trainerScale = 296,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_Ripplade,
        .frontPicSize = MON_COORDS_SIZE(56, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_VIBRATE,
        .backPic = gMonBackPic_Ripplade,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 3,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Ripplade,
        .shinyPalette = gMonShinyPalette_Ripplade,
        .iconSprite = gMonIcon_Gallade,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(7, 13, SHADOW_SIZE_L)
        FOOTPRINT(Gallade)
        OVERWORLD(
            sPicTable_Gallade,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Gallade,
            gShinyOverworldPalette_Gallade
        )
        .levelUpLearnset = sRippladeLevelUpLearnset,
        .teachableLearnset = sGalladeTeachableLearnset,
    },
	
	[SPECIES_MANUHITA] =
    {
        .baseHP        = 59,
        .baseAttack    = 46,
        .baseDefense   = 74,
        .baseSpeed     = 23,
        .baseSpAttack  = 27,
        .baseSpDefense = 38,
        .types = MON_TYPES(TYPE_FIRE, TYPE_STEEL),
        .catchRate = 180,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 47 : 87,
        .evYield_HP = 1,
        .itemRare = ITEM_BLACK_BELT,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_MAGMA_ARMOR, ABILITY_FLASH_FIRE, ABILITY_HEAVY_METAL },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Manuhita"),
        .cryId = CRY_MAKUHITA,
        .natDexNum = NATIONAL_DEX_MAKUHITA,
        .categoryName = _("Iron Shogun"),
        .height = 10,
        .weight = 864,
        .description = COMPOUND_STRING(
            "Its heavy armor plating can withstand\n"
            "the hottest magma. It hardens its\n"
            "heavy steel fists in fire before\n"
            "unleashing devastating punches."),
        .pokemonScale = 256,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Manuhita,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 12 : 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_SWING_CONCAVE : ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Manuhita,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(56, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 8,
        .backAnimId = BACK_ANIM_SHAKE_GLOW_RED,
        .palette = gMonPalette_Manuhita,
        .shinyPalette = gMonShinyPalette_Manuhita,
        .iconSprite = gMonIcon_Makuhita,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 10, SHADOW_SIZE_L)
        FOOTPRINT(Makuhita)
        OVERWORLD(
            sPicTable_Makuhita,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Makuhita,
            gShinyOverworldPalette_Makuhita
        )
        .levelUpLearnset = sManuhitaLevelUpLearnset,
        .teachableLearnset = sMakuhitaTeachableLearnset,
        .eggMoveLearnset = sMakuhitaEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_FURNIYAMA}),
    },

    [SPECIES_FURNIYAMA] =
    {
        .baseHP        = 85,
        .baseAttack    = 85,
        .baseDefense   = 109,
        .baseSpeed     = 70,
        .baseSpAttack  = 50,
        .baseSpDefense = 105,
        .types = MON_TYPES(TYPE_FIRE, TYPE_STEEL),
        .catchRate = 200,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 166 : 184,
        .evYield_HP = 2,
        .itemRare = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_STAMINA, ABILITY_FLASH_FIRE, ABILITY_HEAVY_METAL },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Furniyama"),
        .cryId = CRY_HARIYAMA,
        .natDexNum = NATIONAL_DEX_HARIYAMA,
        .categoryName = _("Iron Shogun"),
        .height = 23,
        .weight = 2538,
        .description = COMPOUND_STRING(
            "The molten iron within its core\n"
            "reaches extreme temperatures. It\n"
            "plants its heavy feet firmly to\n"
            "deflect incoming attacks with ease."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 343,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_Furniyama,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_ROTATE_UP_TO_SIDES,
        .backPic = gMonBackPic_Furniyama,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 4,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_Furniyama,
        .shinyPalette = gMonShinyPalette_Furniyama,
        .iconSprite = gMonIcon_Hariyama,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 9, SHADOW_SIZE_L)
        FOOTPRINT(Hariyama)
        OVERWORLD(
            sPicTable_Hariyama,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Hariyama,
            gShinyOverworldPalette_Hariyama
        )
        .levelUpLearnset = sFurniyamaLevelUpLearnset,
        .teachableLearnset = sHariyamaTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 45, SPECIES_KILOZUNA}),
    },
	
	[SPECIES_KILOZUNA] =
    {
        .baseHP        = 105,
        .baseAttack    = 90,
        .baseDefense   = 135,
        .baseSpeed     = 75,
        .baseSpAttack  = 55,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_FIRE, TYPE_STEEL),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 211 : 213,
        .evYield_HP = 2,
        .itemRare = ITEM_KINGS_ROCK,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_FLUCTUATING,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_STAMINA, ABILITY_FLASH_FIRE, ABILITY_HEAVY_METAL },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Kilozuna"),
        .cryId = CRY_HARIYAMA,
        .natDexNum = NATIONAL_DEX_HARIYAMA,
        .categoryName = _("Shogun"),
        .height = 23,
        .weight = 2538,
        .description = COMPOUND_STRING(
            "Weighing a kiloton, its steel\n"
            "body radiates blistering heat.\n"
            "A single stomp can crack the earth\n"
            "and release bursts of molten iron."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 343,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_Kilozuna,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE_SLOW,
        .backPic = gMonBackPic_Kilozuna,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 4,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Kilozuna,
        .shinyPalette = gMonShinyPalette_Kilozuna,
        .iconSprite = gMonIcon_Hariyama,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 9, SHADOW_SIZE_L)
        FOOTPRINT(Hariyama)
        OVERWORLD(
            sPicTable_Hariyama,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Hariyama,
            gShinyOverworldPalette_Hariyama
        )
        .levelUpLearnset = sKilozunaLevelUpLearnset,
        .teachableLearnset = sHariyamaTeachableLearnset,
    },
	
	[SPECIES_WHIZMUR] =
    {
        .baseHP        = 84,
        .baseAttack    = 36,
        .baseDefense   = 53,
        .baseSpeed     = 19,
        .baseSpAttack  = 45,
        .baseSpDefense = 63,
        .types = MON_TYPES(TYPE_GHOST, TYPE_ELECTRIC),
        .catchRate = 190,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 48 : 68,
        .evYield_HP = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_FIELD),
        .abilities = { ABILITY_SOUNDPROOF, ABILITY_GALVANIZE, ABILITY_LIGHTNING_ROD },
        .bodyColor = BODY_COLOR_PINK,
        .speciesName = _("Whizmur"),
        .cryId = CRY_WHISMUR,
        .natDexNum = NATIONAL_DEX_WHISMUR,
        .categoryName = _("Radio"),
        .height = 6,
        .weight = 163,
        .description = COMPOUND_STRING(
            "It wears a headset that crackles\n"
           "with high-voltage audio frequencies.\n"
            "It communicates through shortwave\n"
            "radio static when it is startled."),
        .pokemonScale = 373,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Whizmur,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 40) : MON_COORDS_SIZE(48, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 14 : 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_Whizmur,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 40) : MON_COORDS_SIZE(56, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 0,
        .backAnimId = BACK_ANIM_SHAKE_FLASH_YELLOW,
        .palette = gMonPalette_Whizmur,
        .shinyPalette = gMonShinyPalette_Whizmur,
        .iconSprite = gMonIcon_Whismur,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 0 : 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(0, 8, SHADOW_SIZE_S)
        FOOTPRINT(Whismur)
        OVERWORLD(
            sPicTable_Whismur,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Whismur,
            gShinyOverworldPalette_Whismur
        )
        .levelUpLearnset = sWhizmurLevelUpLearnset,
        .teachableLearnset = sWhismurTeachableLearnset,
        .eggMoveLearnset = sWhismurEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_VOLTRED}),
    },

    [SPECIES_VOLTRED] =
    {
        .baseHP        = 104,
        .baseAttack    = 62,
        .baseDefense   = 73,
        .baseSpeed     = 39,
        .baseSpAttack  = 71,
        .baseSpDefense = 83,
        .types = MON_TYPES(TYPE_GHOST, TYPE_ELECTRIC),
        .catchRate = 120,
        .expYield = 126,
        .evYield_HP = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_FIELD),
        .abilities = { ABILITY_SOUNDPROOF, ABILITY_GALVANIZE, ABILITY_LIGHTNING_ROD },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Voltred"),
        .cryId = CRY_LOUDRED,
        .natDexNum = NATIONAL_DEX_LOUDRED,
        .categoryName = _("Big Voice"),
        .height = 10,
        .weight = 405,
        .description = COMPOUND_STRING(
            "It generates electrical power by\n"
            "screaming into the void. The ghostly\n"
            "currents swirling around its face\n"
           "will shock anyone who gets too close."),
        .pokemonScale = 356,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Voltred,
        .frontPicSize = MON_COORDS_SIZE(56, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_BOUNCE_ROTATE_TO_SIDES_SLOW : ANIM_SHRINK_GROW,
        .backPic = gMonBackPic_Voltred,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 48) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 2,
        .backAnimId = BACK_ANIM_GROW_STUTTER,
        .palette = gMonPalette_Voltred,
        .shinyPalette = gMonShinyPalette_Voltred,
        .iconSprite = gMonIcon_Loudred,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 17, SHADOW_SIZE_L)
        FOOTPRINT(Loudred)
        OVERWORLD(
            sPicTable_Loudred,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Loudred,
            gShinyOverworldPalette_Loudred
        )
        .levelUpLearnset = sVoltredLevelUpLearnset,
        .teachableLearnset = sLoudredTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_EXHERTZ}),
    },

    [SPECIES_EXHERTZ] =
    {
        .baseHP        = 134,
        .baseAttack    = 61,
        .baseDefense   = 103,
        .baseSpeed     = 98,
        .baseSpAttack  = 91,
        .baseSpDefense = P_UPDATED_STATS >= GEN_6 ? 123 : 113,
        .types = MON_TYPES(TYPE_GHOST, TYPE_ELECTRIC),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 245,
    #elif P_UPDATED_EXP_YIELDS >= GEN_6
        .expYield = 221,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 216,
    #else
        .expYield = 184,
    #endif
        .evYield_HP = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER, EGG_GROUP_FIELD),
        .abilities = { ABILITY_SOUNDPROOF, ABILITY_GALVANIZE, ABILITY_LIGHTNING_ROD },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Exhertz"),
        .cryId = CRY_EXPLOUD,
        .natDexNum = NATIONAL_DEX_EXPLOUD,
        .categoryName = _("Loud Noise"),
        .height = 15,
        .weight = 840,
        .description = COMPOUND_STRING(
           "By vibrating its ghostly body at high\n"
           "frequencies, it generates over one\n"
           "million hertz of electrical sound.\n"
           "A single roar can shatter solid stone."),
        .pokemonScale = 284,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Exhertz,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_FLICKER,
        .backPic = gMonBackPic_Exhertz,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 3 : 0,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        .palette = gMonPalette_Exhertz,
        .shinyPalette = gMonShinyPalette_Exhertz,
        .iconSprite = gMonIcon_Exploud,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 17, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Exploud)
        OVERWORLD(
            sPicTable_Exploud,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Exploud,
            gShinyOverworldPalette_Exploud
        )
        .levelUpLearnset = sExhertzLevelUpLearnset,
        .teachableLearnset = sExploudTeachableLearnset,
    },
	
	[SPECIES_BAYRON] =
    {
        .baseHP        = 54,
        .baseAttack    = 70,
        .baseDefense   = 76,
        .baseSpeed     = 26,
        .baseSpAttack  = 40,
        .baseSpDefense = 64,
        .types = MON_TYPES(TYPE_WATER, TYPE_ROCK),
        .catchRate = 180,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 66 : 96,
        .evYield_Defense = 1,
        .itemRare = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
        .abilities = { ABILITY_HYDRATION, ABILITY_SOLID_ROCK, ABILITY_TORRENT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Bayron"),
        .cryId = CRY_ARON,
        .natDexNum = NATIONAL_DEX_ARON,
        .categoryName = _("Iron Armor"),
        .height = 4,
        .weight = 600,
        .description = COMPOUND_STRING(
            "It plays along rocky shores, letting\n"
            "rough ocean waves batter its stone\n"
            "hide. It stores seawater in its vents\n"
            "to keep its mossy spikes damp."),
        .pokemonScale = 419,
        .pokemonOffset = 23,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bayron,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 24) : MON_COORDS_SIZE(32, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 20 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .backPic = gMonBackPic_Bayron,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 32) : MON_COORDS_SIZE(48, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 17 : 0,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_Bayron,
        .shinyPalette = gMonShinyPalette_Bayron,
        .iconSprite = gMonIcon_Aron,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(2, 12, SHADOW_SIZE_S)
        FOOTPRINT(Aron)
        OVERWORLD(
            sPicTable_Aron,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Aron,
            gShinyOverworldPalette_Aron
        )
        .levelUpLearnset = sBayronLevelUpLearnset,
        .teachableLearnset = sAronTeachableLearnset,
        .eggMoveLearnset = sAronEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_TAIRON}),
    },

    [SPECIES_TAIRON] =
    {
        .baseHP        = 64,
        .baseAttack    = 91,
        .baseDefense   = 98,
        .baseSpeed     = 47,
        .baseSpAttack  = 44,
        .baseSpDefense = 86,
        .types = MON_TYPES(TYPE_WATER, TYPE_ROCK),
        .catchRate = 90,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 151 : 152,
        .evYield_Defense = 2,
        .itemRare = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
        .abilities = { ABILITY_SHELL_ARMOR, ABILITY_SOLID_ROCK, ABILITY_TORRENT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Tairon"),
        .cryId = CRY_LAIRON,
        .natDexNum = NATIONAL_DEX_LAIRON,
        .categoryName = _("Iron Armor"),
        .height = 9,
        .weight = 1200,
        .description = COMPOUND_STRING(
           "It lives along stormy coastlines.\n"
            "By letting rough waves batter its stone\n"
            "body, it encourages the growth of a\n"
            "special sea moss that hardens its shell."),
        .pokemonScale = 275,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tairon,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 40) : MON_COORDS_SIZE(56, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tairon,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 32) : MON_COORDS_SIZE(64, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 17 : 0,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_Tairon,
        .shinyPalette = gMonShinyPalette_Tairon,
        .iconSprite = gMonIcon_Lairon,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 13, SHADOW_SIZE_L)
        FOOTPRINT(Lairon)
        OVERWORLD(
            sPicTable_Lairon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Lairon,
            gShinyOverworldPalette_Lairon
        )
        .levelUpLearnset = sTaironLevelUpLearnset,
        .teachableLearnset = sLaironTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_CRAGGRON}),
    },

    [SPECIES_CRAGGRON] =
    {
        .baseHP        = 70,
        .baseAttack    = 115,
        .baseDefense   = 140,
        .baseSpeed     = 55,
        .baseSpAttack  = 50,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_WATER, TYPE_ROCK),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 265,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 239,
    #else
        .expYield = 205,
    #endif
        .evYield_Defense = 3,
        .itemRare = ITEM_HARD_STONE,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 35,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
        .abilities = { ABILITY_WEAK_ARMOR, ABILITY_SOLID_ROCK, ABILITY_SHEER_FORCE },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Craggron"),
        .cryId = CRY_AGGRON,
        .natDexNum = NATIONAL_DEX_AGGRON,
        .categoryName = _("Iron Armor"),
        .height = 21,
        .weight = 3600,
        .description = COMPOUND_STRING(
            "Its hollow armor stores a massive\n"
            "volume of seawater. It can unleash\n"
            "a devastating torrent from its chest\n"
            "to smash ships that venture too close."),
        .pokemonScale = 256,
        .pokemonOffset = -1,
        .trainerScale = 350,
        .trainerOffset = 6,
        .frontPic = gMonFrontPic_Craggron,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_SHRINK_GROW_VIBRATE,
        .backPic = gMonBackPic_Craggron,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 0,
        .backAnimId = ANIM_V_STRETCH_BOTH_ENDS_SLOW,
        .palette = gMonPalette_Craggron,
        .shinyPalette = gMonShinyPalette_Craggron,
        .iconSprite = gMonIcon_Aggron,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(5, 13, SHADOW_SIZE_L)
        FOOTPRINT(Aggron)
        OVERWORLD(
            sPicTable_Aggron,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Aggron,
            gShinyOverworldPalette_Aggron
        )
        .levelUpLearnset = sCraggronLevelUpLearnset,
        .teachableLearnset = sAggronTeachableLearnset,
    },
	
	[SPECIES_BAUBLEYE] =
    {
        .baseHP        = 70,
        .baseAttack    = 75,
        .baseDefense   = 80,
        .baseSpeed     = 50,
        .baseSpAttack  = 65,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_STEEL, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 133 : 98,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .itemRare = ITEM_WIDE_LENS,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = 35,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_MAGIC_GUARD, ABILITY_STEELWORKER, ABILITY_FRIEND_GUARD },
    #else
        .abilities = { ABILITY_MAGIC_GUARD, ABILITY_STEELWORKER, ABILITY_FRIEND_GUARD },
    #endif
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("Baubleye"),
        .cryId = CRY_SABLEYE,
        .natDexNum = NATIONAL_DEX_SABLEYE,
        .categoryName = _("Darkness"),
        .height = 5,
        .weight = 110,
        .description = COMPOUND_STRING(
            "It hoards shiny metal trinkets and\n"
            "attaches them to its body. Its big\n"
            "pink eyes sparkle to hypnotize prey\n"
            "before it steals their belongings."),
        .pokemonScale = 451,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Baubleye,
        .frontPicSize = MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GLOW_BLACK,
        .backPic = gMonBackPic_Baubleye,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(48, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 8 : 0,
        .backAnimId = BACK_ANIM_H_VIBRATE,
        .palette = gMonPalette_Baubleye,
        .shinyPalette = gMonShinyPalette_Baubleye,
        .iconSprite = gMonIcon_Sableye,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(2, 13, SHADOW_SIZE_M)
        FOOTPRINT(Sableye)
        OVERWORLD(
            sPicTable_Sableye,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Sableye,
            gShinyOverworldPalette_Sableye
        )
        .levelUpLearnset = sBaubleyeLevelUpLearnset,
        .teachableLearnset = sSableyeTeachableLearnset,
        .eggMoveLearnset = sSableyeEggMoveLearnset,
    },
	
	[SPECIES_PRISBLU] =
    {
        .baseHP        = 46,
        .baseAttack    = 48,
        .baseDefense   = 62,
        .baseSpeed     = 54,
        .baseSpAttack  = 55,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_FIRE, TYPE_WATER),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 62 : 74,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_FLASH_FIRE, ABILITY_WATER_ABSORB, ABILITY_OVERCOAT },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Prisblu"),
        .cryId = CRY_SWABLU,
        .natDexNum = NATIONAL_DEX_SWABLU,
        .categoryName = _("Cotton Bird"),
        .height = 4,
        .weight = 12,
        .description = COMPOUND_STRING(
            "It boils water within its body to\n"
            "release a fine mist. By catching the\n"
            "sunlight, its wings glow with the\n"
            "brilliant colors of a prism."),
        .pokemonScale = 422,
        .pokemonOffset = -8,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Prisblu,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(48, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 17 : 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_SLIDE : ANIM_GROW_VIBRATE,
        .enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 12 : 0,
        .backPic = gMonBackPic_Prisblu,
        .backPicSize = MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 14,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        .palette = gMonPalette_Prisblu,
        .shinyPalette = gMonShinyPalette_Prisblu,
        .iconSprite = gMonIcon_Swablu,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 7, SHADOW_SIZE_S)
        FOOTPRINT(Swablu)
        OVERWORLD(
            sPicTable_Swablu,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Swablu,
            gShinyOverworldPalette_Swablu
        )
        .levelUpLearnset = sPrisbluLevelUpLearnset,
        .teachableLearnset = sSwabluTeachableLearnset,
        .eggMoveLearnset = sSwabluEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_IRISARIA}),
    },

    [SPECIES_IRISARIA] =
    {
        .baseHP        = 72,
        .baseAttack    = 68,
        .baseDefense   = 82,
        .baseSpeed     = 78,
        .baseSpAttack  = 95,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_FIRE, TYPE_WATER),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 172 : 188,
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_ERRATIC,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING, EGG_GROUP_DRAGON),
        .abilities = { ABILITY_LEVITATE, ABILITY_WATER_ABSORB, ABILITY_OVERCOAT },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Irisaria"),
        .cryId = CRY_ALTARIA,
        .natDexNum = NATIONAL_DEX_ALTARIA,
        .categoryName = _("Humming"),
        .height = 11,
        .weight = 206,
        .description = COMPOUND_STRING(
            "Its magnificent wings are made of\n"
            "scalding water vapor. When it\n"
            "soars, its intense heat refracts\n"
            "light into a spectacular rainbow."),
        .pokemonScale = 327,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Irisaria,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 2 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_H_STRETCH : ANIM_V_STRETCH,
        .enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 0,
        .backPic = gMonBackPic_Irisaria,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 6 : 0,
        .backAnimId = BACK_ANIM_CONVEX_DOUBLE_ARC,
        .palette = gMonPalette_Irisaria,
        .shinyPalette = gMonShinyPalette_Irisaria,
        .iconSprite = gMonIcon_Altaria,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 16, SHADOW_SIZE_L)
        FOOTPRINT(Altaria)
        OVERWORLD(
            sPicTable_Altaria,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Altaria,
            gShinyOverworldPalette_Altaria
        )
        .levelUpLearnset = sIrisariaLevelUpLearnset,
        .teachableLearnset = sAltariaTeachableLearnset,
    },
	
	[SPECIES_SNOPINCH] =
    {
        .baseHP        = 45,
        .baseAttack    = 110,
        .baseDefense   = 35,
        .baseSpeed     = 20,
        .baseSpAttack  = 45,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_ICE, TYPE_BUG),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 58 : 73,
        .evYield_Attack = 1,
        .itemRare = ITEM_SOFT_SAND,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = TRAPINCH_FAMILY_EGG_GROUPS,
        .abilities = { ABILITY_REFRIGERATE, ABILITY_STRONG_JAW, ABILITY_SNOW_WARNING },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Snopinch"),
        .cryId = CRY_TRAPINCH,
        .natDexNum = NATIONAL_DEX_TRAPINCH,
        .categoryName = _("Ant Pit"),
        .height = 7,
        .weight = 150,
        .description = COMPOUND_STRING(
            "Its massive head is composed of dense,\n"
            "unmelting ice. It stays warm within\n"
            "its thick coat of snow-fur while\n"
           "waiting for prey to cross its path."),
        .pokemonScale = 298,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Snopinch,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 32) : MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 16 : 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE,
        .backPic = gMonBackPic_Snopinch,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 40) : MON_COORDS_SIZE(48, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 14 : 10,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Snopinch,
        .shinyPalette = gMonShinyPalette_Snopinch,
        .iconSprite = gMonIcon_Trapinch,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(4, 3, SHADOW_SIZE_M)
        FOOTPRINT(Trapinch)
        OVERWORLD(
            sPicTable_Trapinch,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Trapinch,
            gShinyOverworldPalette_Trapinch
        )
        .levelUpLearnset = sSnopinchLevelUpLearnset,
        .teachableLearnset = sTrapinchTeachableLearnset,
        .eggMoveLearnset = sTrapinchEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 18, SPECIES_FROSTRAVA}),
    },

    [SPECIES_FROSTRAVA] =
    {
        .baseHP        = 50,
        .baseAttack    = 80,
        .baseDefense   = 40,
        .baseSpeed     = 80,
        .baseSpAttack  = 70,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_ICE, TYPE_BUG),
        .catchRate = 120,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 119 : 126,
        .evYield_Attack = 1,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = TRAPINCH_FAMILY_EGG_GROUPS,
        .abilities = { ABILITY_REFRIGERATE, ABILITY_OVERCOAT, ABILITY_SNOW_WARNING },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Frostrava"),
        .cryId = CRY_VIBRAVA,
        .natDexNum = NATIONAL_DEX_VIBRAVA,
        .categoryName = _("Vibration"),
        .height = 11,
        .weight = 153,
        .description = COMPOUND_STRING(
            "Its wings are solid sheets of ice.\n"
            "By vibrating them at high speeds,\n"
            "it generates freezing gales that\n"
            "can instantly freeze its prey."),
        .pokemonScale = 370,
        .pokemonOffset = 11,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Frostrava,
        .frontPicSize = MON_COORDS_SIZE(64, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 12 : 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SHAKE,
        .backPic = gMonBackPic_Frostrava,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 32) : MON_COORDS_SIZE(64, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 17 : 12,
        .backAnimId = BACK_ANIM_H_VIBRATE,
        .palette = gMonPalette_Frostrava,
        .shinyPalette = gMonShinyPalette_Frostrava,
        .iconSprite = gMonIcon_Vibrava,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 9, SHADOW_SIZE_L)
        FOOTPRINT(Vibrava)
        OVERWORLD(
            sPicTable_Vibrava,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Vibrava,
            gShinyOverworldPalette_Vibrava
        )
        .levelUpLearnset = sFrostravaLevelUpLearnset,
        .teachableLearnset = sVibravaTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_FLURROGON}),
    },

    [SPECIES_FLURROGON] =
    {
        .baseHP        = 80,
        .baseAttack    = 100,
        .baseDefense   = 80,
        .baseSpeed     = 100,
        .baseSpAttack  = 100,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_ICE, TYPE_BUG),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 260,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 234,
    #else
        .expYield = 197,
    #endif
        .evYield_Attack = 1,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = TRAPINCH_FAMILY_EGG_GROUPS,
        .abilities = { ABILITY_REFRIGERATE, ABILITY_OVERCOAT, ABILITY_SNOW_WARNING },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Flurrogon"),
        .cryId = CRY_FLYGON,
        .natDexNum = NATIONAL_DEX_FLYGON,
        .categoryName = _("Mystic"),
        .height = 20,
        .weight = 820,
        .description = COMPOUND_STRING(
            "By flapping its glacial wings, it\n"
            "whips up blinding snowstorms. The\n"
            "sound of its flight resembles a\n"
            "soft, beautiful winter whistle."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 268,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_Flurrogon,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_ZIGZAG_SLOW,
        .enemyMonElevation = 7,
        .backPic = gMonBackPic_Flurrogon,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 2 : 3,
        .backAnimId = BACK_ANIM_TRIANGLE_DOWN,
        .palette = gMonPalette_Flurrogon,
        .shinyPalette = gMonShinyPalette_Flurrogon,
        .iconSprite = gMonIcon_Flygon,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(6, 17, SHADOW_SIZE_L)
        FOOTPRINT(Flygon)
        OVERWORLD(
            sPicTable_Flygon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Flygon,
            gShinyOverworldPalette_Flygon
        )
        .levelUpLearnset = sFlurrogonLevelUpLearnset,
        .teachableLearnset = sFlygonTeachableLearnset,
    },
	
	[SPECIES_DIGON] =
    {
        .baseHP        = 50,
        .baseAttack    = 65,
        .baseDefense   = 55,
        .baseSpeed     = 60,
        .baseSpAttack  = 40,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GROUND, TYPE_DARK),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 60 : 89,
        .evYield_Attack = 1,
        .itemRare = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON),
        .abilities = { ABILITY_STAKEOUT, ABILITY_EARTH_EATER, ABILITY_STRONG_JAW },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Digon"),
        .cryId = CRY_BAGON,
        .natDexNum = NATIONAL_DEX_BAGON,
        .categoryName = _("Rock Head"),
        .height = 6,
        .weight = 421,
        .description = COMPOUND_STRING(
            "An aggressive bug that spends its entire\n"
            "powerful because its body is a bundle of\n"
            "muscles. It launches head-butts with its\n"
            "ironlike skull."),
        .pokemonScale = 448,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Digon,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 48) : MON_COORDS_SIZE(32, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 9,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
        ),
        .frontAnimId = ANIM_H_SLIDE_SLOW,
        .backPic = gMonBackPic_Digon,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 8 : 0,
        .backAnimId = BACK_ANIM_H_SLIDE,
        .palette = gMonPalette_Digon,
        .shinyPalette = gMonShinyPalette_Digon,
        .iconSprite = gMonIcon_Bagon,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-2, 1, SHADOW_SIZE_S)
        FOOTPRINT(Bagon)
        OVERWORLD(
            sPicTable_Bagon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Bagon,
            gShinyOverworldPalette_Bagon
        )
        .levelUpLearnset = sDigonLevelUpLearnset,
        .teachableLearnset = sBagonTeachableLearnset,
        .eggMoveLearnset = sBagonEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_BURROGON}),
    },

    [SPECIES_BURROGON] =
    {
        .baseHP        = 75,
        .baseAttack    = 90,
        .baseDefense   = 85,
        .baseSpeed     = 70,
        .baseSpAttack  = 45,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_GROUND, TYPE_DARK),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 147 : 144,
        .evYield_Defense = 2,
        .itemRare = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON),
        .abilities = { ABILITY_STAKEOUT, ABILITY_EARTH_EATER, ABILITY_STRONG_JAW },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Burrogon"),
        .cryId = CRY_SHELGON,
        .natDexNum = NATIONAL_DEX_SHELGON,
        .categoryName = _("Endurance"),
        .height = 11,
        .weight = 1105,
        .description = COMPOUND_STRING(
            "While its armored head rests above the\n"
            "clay, its tail maneuvers through a\n"
            "separate tunnel. It can strike prey\n"
            "from two directions at once."),
        .pokemonScale = 311,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Burrogon,
        .frontPicSize = MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = 15,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
        ),
        .frontAnimId = ANIM_V_SHAKE_TWICE_SLOW,
        .backPic = gMonBackPic_Burrogon,
        .backPicSize = MON_COORDS_SIZE(64, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 9,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_Burrogon,
        .shinyPalette = gMonShinyPalette_Burrogon,
        .iconSprite = gMonIcon_Shelgon,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(16, -5, SHADOW_SIZE_S)
        FOOTPRINT(Shelgon)
        OVERWORLD(
            sPicTable_Shelgon,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Shelgon,
            gShinyOverworldPalette_Shelgon
        )
        .levelUpLearnset = sBurrogonLevelUpLearnset,
        .teachableLearnset = sShelgonTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 50, SPECIES_TERRAMENCE}),
    },

    [SPECIES_TERRAMENCE] =
    {
        .baseHP        = 95,
        .baseAttack    = 135,
        .baseDefense   = 110,
        .baseSpeed     = 100,
        .baseSpAttack  = 80,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GROUND, TYPE_DARK),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 300,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 270,
    #else
        .expYield = 218,
    #endif
        .evYield_Attack = 3,
        .itemRare = ITEM_DRAGON_FANG,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_DRAGON),
        .abilities = { ABILITY_STAKEOUT, ABILITY_EARTH_EATER, ABILITY_STRONG_JAW },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Terramence"),
        .cryId = CRY_SALAMENCE,
        .natDexNum = NATIONAL_DEX_SALAMENCE,
        .categoryName = _("Dragon"),
        .height = 15,
        .weight = 1026,
        .description = COMPOUND_STRING(
            "It tunnels through bedrock with immense\n"
            "speed. When it coils its massive,\n"
            "segmented body beneath the earth,\n"
            "it triggers localized earthquakes."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Terramence,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 10,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 10),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 30),
            ANIMCMD_FRAME(1, 15),
            ANIMCMD_FRAME(0, 15),
        ),
        .frontAnimId = ANIM_H_SHAKE,
        .backPic = gMonBackPic_Terramence,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(56, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 6 : 4,
        .backAnimId = BACK_ANIM_H_SHAKE,
        .palette = gMonPalette_Terramence,
        .shinyPalette = gMonShinyPalette_Terramence,
        .iconSprite = gMonIcon_Salamence,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-13, 5, SHADOW_SIZE_S)
        FOOTPRINT(Salamence)
        OVERWORLD(
            sPicTable_Salamence,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Salamence,
            gShinyOverworldPalette_Salamence
        )
        .levelUpLearnset = sTerramenceLevelUpLearnset,
        .teachableLearnset = sSalamenceTeachableLearnset,
    },
	
	//Convergent Paldea
	[SPECIES_BLOCLI] =
    {
        .baseHP        = 55,
        .baseAttack    = 40,
        .baseDefense   = 65,
        .baseSpeed     = 25,
        .baseSpAttack  = 40,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 255,
        .expYield = 56,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_IMMUNITY, ABILITY_OVERCOAT, ABILITY_FRIEND_GUARD },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Blocli"),
        .cryId = CRY_NACLI,
        .natDexNum = NATIONAL_DEX_NACLI,
        .categoryName = _("Rock Salt"),
        .height = 4,
        .weight = 160,
        .description = COMPOUND_STRING(
            "It wanders around toy shops and nurseries\n"
            "to blend in with children's playthings.\n"
            "If anyone attempts to stack it, it\n"
            "startles them by suddenly walking away."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Blocli,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_BACK_AND_LUNGE,
        .backPic = gMonBackPic_Blocli,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 15,
        .backAnimId = BACK_ANIM_H_SLIDE,
        .palette = gMonPalette_Blocli,
        .shinyPalette = gMonShinyPalette_Blocli,
        .iconSprite = gMonIcon_Nacli,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-1, 5, SHADOW_SIZE_S)
        FOOTPRINT(Nacli)
        OVERWORLD(
            sPicTable_Nacli,
            SIZE_32x32,
            SHADOW_SIZE_S,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Nacli,
            gShinyOverworldPalette_Nacli
        )
        .levelUpLearnset = sNacliLevelUpLearnset,
        .teachableLearnset = sNacliTeachableLearnset,
        .eggMoveLearnset = sNacliEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_BLOXTACK}),
    },

    [SPECIES_BLOXTACK] =
    {
        .baseHP        = 65,
        .baseAttack    = 60,
        .baseDefense   = 80,
        .baseSpeed     = 25,
        .baseSpAttack  = 50,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 120,
        .expYield = 124,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_IMMUNITY, ABILITY_OVERCOAT, ABILITY_FRIEND_GUARD },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Bloxtack"),
        .cryId = CRY_NACLSTACK,
        .natDexNum = NATIONAL_DEX_NACLSTACK,
        .categoryName = _("Rock Salt"),
        .height = 6,
        .weight = 1050,
        .description = COMPOUND_STRING(
            "It moves with stiff, geometric strides.\n"
            "If its blocky shell is damaged in a\n"
            "fight, it repairs itself by gathering\n"
            "discarded toy blocks from houses."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bloxtack,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_STRETCH,
        .backPic = gMonBackPic_Bloxtack,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_Bloxtack,
        .shinyPalette = gMonShinyPalette_Bloxtack,
        .iconSprite = gMonIcon_Naclstack,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(0, 3, SHADOW_SIZE_L)
        FOOTPRINT(Naclstack)
        OVERWORLD(
            sPicTable_Naclstack,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Naclstack,
            gShinyOverworldPalette_Naclstack
        )
        .levelUpLearnset = sNaclstackLevelUpLearnset,
        .teachableLearnset = sNaclstackTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 38, SPECIES_GARGABLOX}),
    },

    [SPECIES_GARGABLOX] =
    {
        .baseHP        = 95,
        .baseAttack    = 80,
        .baseDefense   = 110,
        .baseSpeed     = 25,
        .baseSpAttack  = 80,
        .baseSpDefense = 110,
        .types = MON_TYPES(TYPE_NORMAL),
        .catchRate = 45,
        .expYield = 250,
        .evYield_Defense = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MINERAL),
        .abilities = { ABILITY_IMMUNITY, ABILITY_OVERCOAT, ABILITY_FRIEND_GUARD },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Gargablox"),
        .cryId = CRY_GARGANACL,
        .natDexNum = NATIONAL_DEX_GARGANACL,
        .categoryName = _("Rock Salt"),
        .height = 23,
        .weight = 2400,
        .description = COMPOUND_STRING(
            "Its colossal body is made of perfectly\n"
            "balanced prisms. A single blow from\n"
            "its heavy, interlocking block fists\n"
            "can level a modern brick house."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Gargablox,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Gargablox,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 10,
        .backAnimId = BACK_ANIM_H_VIBRATE,
        .palette = gMonPalette_Gargablox,
        .shinyPalette = gMonShinyPalette_Gargablox,
        .iconSprite = gMonIcon_Garganacl,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 13, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Garganacl)
        OVERWORLD(
            sPicTable_Garganacl,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Garganacl,
            gShinyOverworldPalette_Garganacl
        )
        .levelUpLearnset = sGarganaclLevelUpLearnset,
        .teachableLearnset = sGarganaclTeachableLearnset,
    },
	
	//Hoennian Forms
	[SPECIES_ABRA_HOENN] =
    {
        .baseHP        = 25,
        .baseAttack    = 20,
        .baseDefense   = 55,
        .baseSpeed     = 90,
        .baseSpAttack  = 105,
        .baseSpDefense = 15,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 200,
    #if P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 62,
    #elif P_UPDATED_EXP_YIELDS >= GEN_4
        .expYield = 75,
    #else
        .expYield = 73,
    #endif
        .evYield_SpAttack = 1,
        .itemRare = ITEM_BLACK_GLASSES,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_PRANKSTER, ABILITY_PICKPOCKET },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Abra"),
        .cryId = CRY_ABRA,
        .natDexNum = NATIONAL_DEX_ABRA,
        .categoryName = _("Psi"),
        .height = 9,
        .weight = 195,
        .description = COMPOUND_STRING(
            "It spends up to 18 hours a day sleeping in\n"
            "deep shadows. If it senses a threat while\n"
            "asleep, it instinctively uses its dark powers\n"
            "to slip away into the nearest reflection."),
        .pokemonScale = 363,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_AbraHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_H_JUMPS : ANIM_H_VIBRATE,
        .backPic = gMonBackPic_AbraHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 12,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_AbraHoenn,
        .shinyPalette = gMonShinyPalette_AbraHoenn,
        .iconSprite = gMonIcon_Abra,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 3, SHADOW_SIZE_L)
        FOOTPRINT(Abra)
        OVERWORLD(
            sPicTable_Abra,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Abra,
            gShinyOverworldPalette_Abra
        )
        .levelUpLearnset = sAbraHoennLevelUpLearnset,
        .teachableLearnset = sAbraTeachableLearnset,
        .eggMoveLearnset = sAbraEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 16, SPECIES_KADABRA_HOENN}),
    },

    [SPECIES_KADABRA_HOENN] =
    {
        .baseHP        = 40,
        .baseAttack    = 120,
        .baseDefense   = 105,
        .baseSpeed     = 30,
        .baseSpAttack  = 35,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_DARK, TYPE_FIGHTING),
        .catchRate = 100,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 140 : 145,
        .evYield_SpAttack = 2,
        .itemRare = ITEM_TWISTED_SPOON,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_INNER_FOCUS, ABILITY_PICKPOCKET },
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = TRUE,
        .speciesName = _("Kadabra"),
        .cryId = CRY_KADABRA,
        .natDexNum = NATIONAL_DEX_KADABRA,
        .categoryName = _("Psi"),
        .height = 13,
        .weight = 565,
        .description = COMPOUND_STRING(
            "It brandishes a heavy wooden club to\n"
            "subdue its targets. Its newly gained\n"
            "fighting instincts make it extremely\n"
            "aggressive when backed into a corner."),
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_KadabraHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_KadabraHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 8,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_KadabraHoenn,
        .shinyPalette = gMonShinyPalette_KadabraHoenn,
        .iconSprite = gMonIcon_Kadabra,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 6, SHADOW_SIZE_L)
        FOOTPRINT(Kadabra)
        OVERWORLD(
            sPicTable_Kadabra,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following_Asym,
            gOverworldPalette_Kadabra,
            gShinyOverworldPalette_Kadabra
        )
        .levelUpLearnset = sKadabraHoennLevelUpLearnset,
        .teachableLearnset = sKadabraTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_ALAKAZAM_HOENN}),
                               
    },


    [SPECIES_ALAKAZAM_HOENN] =
    {
        .baseHP        = 55,
        .baseAttack    = 50,
        .baseDefense   = 95,
        .baseSpeed     = 120,
        .baseSpAttack  = 135,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 50,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 250,
    #elif P_UPDATED_EXP_YIELDS >= GEN_6
        .expYield = 225,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 221,
    #else
        .expYield = 186,
    #endif
        .evYield_SpAttack = 3,
        .itemRare = ITEM_TWISTED_SPOON,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_SHADOW_TAG, ABILITY_PICKPOCKET },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Alakazam"),
        .cryId = CRY_ALAKAZAM,
        .natDexNum = NATIONAL_DEX_ALAKAZAM,
        .categoryName = _("Psi"),
        .height = 15,
        .weight = 480,
        .description = COMPOUND_STRING(
            "It no longer needs physical weapons,\n"
            "relying instead on pure malice to\n"
            "paralyze prey. It thoroughly enjoys\n"
            "tormenting weaker Pokémon in the dark."),
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_AlakazamHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_STRETCH : ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_AlakazamHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 56) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 6,
        .backAnimId = BACK_ANIM_GROW_STUTTER,
        .palette = gMonPalette_AlakazamHoenn,
        .shinyPalette = gMonShinyPalette_AlakazamHoenn,
        .iconSprite = gMonIcon_Alakazam,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 9, SHADOW_SIZE_L)
        FOOTPRINT(Alakazam)
        OVERWORLD(
            sPicTable_Alakazam,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Alakazam,
            gShinyOverworldPalette_Alakazam
        )
        .levelUpLearnset = sAlakazamHoennLevelUpLearnset,
        .teachableLearnset = sAlakazamTeachableLearnset,
    },
	
	[SPECIES_MACHOP_HOENN] =
    {
        .baseHP        = 50,
        .baseAttack    = 70,
        .baseDefense   = 70,
        .baseSpeed     = 35,
        .baseSpAttack  = 15,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_DRAGON),
        .catchRate = 180,
    #if P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 61,
    #elif P_UPDATED_EXP_YIELDS >= GEN_4
        .expYield = 75,
    #else
        .expYield = 88,
    #endif
        .evYield_Attack = 1,
        .itemRare = ITEM_FOCUS_BAND,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_IRON_FIST, ABILITY_ROUGH_SKIN, ABILITY_NO_GUARD },
    #else
        .abilities = { ABILITY_IRON_FIST, ABILITY_ROUGH_SKIN, ABILITY_NO_GUARD },
    #endif
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Machop"),
        .cryId = CRY_MACHOP,
        .natDexNum = NATIONAL_DEX_MACHOP,
        .categoryName = _("Superpower"),
        .height = 8,
        .weight = 195,
        .description = COMPOUND_STRING(
            "It trains in craggy mountains to harden its\n"
            "dragon scales. Though small, its physical\n"
            "strength is immense. It can easily shatter\n"
            "boulders with a single headbutt."),
        .pokemonScale = 342,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_MachopHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 48) : MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_SQUISH_AND_BOUNCE : ANIM_V_STRETCH,
        .backPic = gMonBackPic_MachopHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 12 : 2,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_MachopHoenn,
        .shinyPalette = gMonShinyPalette_MachopHoenn,
        .iconSprite = gMonIcon_Machop,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 9, SHADOW_SIZE_M)
        FOOTPRINT(Machop)
        OVERWORLD(
            sPicTable_Machop,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Machop,
            gShinyOverworldPalette_Machop
        )
        .levelUpLearnset = sMachopHoennLevelUpLearnset,
        .teachableLearnset = sMachopTeachableLearnset,
        .eggMoveLearnset = sMachopEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 28, SPECIES_MACHOKE_HOENN}),
    },

    [SPECIES_MACHOKE_HOENN] =
    {
        .baseHP        = 60,
        .baseAttack    = 80,
        .baseDefense   = 100,
        .baseSpeed     = 45,
        .baseSpAttack  = 30,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_DRAGON),
        .catchRate = 90,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 142 : 146,
        .evYield_Attack = 2,
        .itemRare = ITEM_FOCUS_BAND,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_IRON_FIST, ABILITY_ROUGH_SKIN, ABILITY_NO_GUARD },
    #else
        .abilities = { ABILITY_IRON_FIST, ABILITY_ROUGH_SKIN, ABILITY_NO_GUARD },
    #endif
        .bodyColor = BODY_COLOR_GRAY,
        .noFlip = TRUE,
        .speciesName = _("Machoke"),
        .cryId = CRY_MACHOKE,
        .natDexNum = NATIONAL_DEX_MACHOKE,
        .categoryName = _("Superpower"),
        .height = 15,
        .weight = 705,
        .description = COMPOUND_STRING(
            "The golden spurs on its arms can slice\n"
            "through solid steel. Its wild, draconic\n"
            "temper makes it difficult to control,\n"
            "and it constantly seeks stronger opponents."),
        .pokemonScale = 323,
        .pokemonOffset = 9,
        .trainerScale = 257,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_MachokeHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 56) : MON_COORDS_SIZE(56, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 6 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
		.frontAnimId = ANIM_V_SHAKE,
        .backPic = gMonBackPic_MachokeHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 2,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_MachokeHoenn,
        .shinyPalette = gMonShinyPalette_MachokeHoenn,
        .iconSprite = gMonIcon_Machoke,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 14, SHADOW_SIZE_L)
        FOOTPRINT(Machoke)
        OVERWORLD(
            sPicTable_Machoke,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Machoke,
            gShinyOverworldPalette_Machoke
        )
        .levelUpLearnset = sMachokeHoennLevelUpLearnset,
        .teachableLearnset = sMachokeTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_MACHAMP_HOENN}),
                                
    },

#if P_UPDATED_EXP_YIELDS >= GEN_8
    #define MACHAMP_EXP_YIELD 253
#elif P_UPDATED_EXP_YIELDS >= GEN_5
    #define MACHAMP_EXP_YIELD 227
#else
    #define MACHAMP_EXP_YIELD 193
#endif

    [SPECIES_MACHAMP_HOENN] =
    {
        .baseHP        = 70,
        .baseAttack    = 110,
        .baseDefense   = 110,
        .baseSpeed     = 55,
        .baseSpAttack  = 45,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_DRAGON),
        .catchRate = 45,
        .expYield = MACHAMP_EXP_YIELD,
        .evYield_Attack = 3,
        .itemRare = ITEM_FOCUS_BAND,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_HUMAN_LIKE),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_IRON_FIST, ABILITY_MULTISCALE, ABILITY_NO_GUARD },
    #else
        .abilities = { ABILITY_IRON_FIST, ABILITY_MULTISCALE, ABILITY_NO_GUARD },
    #endif
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Machamp"),
        .cryId = CRY_MACHAMP,
        .natDexNum = NATIONAL_DEX_MACHAMP,
        .categoryName = _("Superpower"),
        .height = 16,
        .weight = 1300,
        .description = COMPOUND_STRING(
            "An absolute titan of the martial arts.\n"
            "With four powerful arms and unbreakable\n"
            "horns, it unleashes a barrage of draconic\n"
            "punches that can level entire mountains."),
        .pokemonScale = 280,
        .pokemonOffset = 1,
        .trainerScale = 269,
        .trainerOffset = -1,
        .frontPic = gMonFrontPic_MachampHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_JUMPS,
        .backPic = gMonBackPic_MachampHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 56) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 7,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_MachampHoenn,
        .shinyPalette = gMonShinyPalette_MachampHoenn,
        .iconSprite = gMonIcon_Machamp,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(7, 13, SHADOW_SIZE_L)
        FOOTPRINT(Machamp)
        OVERWORLD(
            sPicTable_Machamp,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Machamp,
            gShinyOverworldPalette_Machamp
        )
        .levelUpLearnset = sMachampHoennLevelUpLearnset,
        .teachableLearnset = sMachampTeachableLearnset,
    },
	
	[SPECIES_DODUO_HOENN] =
    {
        .baseHP        = 65,
        .baseAttack    = 95,
        .baseDefense   = 55,
        .baseSpeed     = 75,
        .baseSpAttack  = 25,
        .baseSpDefense = 35,
        .types = MON_TYPES(TYPE_POISON, TYPE_DARK),
        .catchRate = 190,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 62 : 96,
        .evYield_Attack = 1,
        .itemRare = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_MOODY, ABILITY_BIG_PECKS, ABILITY_TANGLED_FEET },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Doduo"),
        .cryId = CRY_DODUO,
        .natDexNum = NATIONAL_DEX_DODUO,
        .categoryName = _("Twin Bird"),
        .height = 14,
        .weight = 392,
        .description = COMPOUND_STRING(
            "It stalks swampy areas under the cover of\n"
            "night. Its two heads rarely cooperate,\n"
            "often snapping viciously at one another\n"
            "as a toxic, purple venom drips from their beaks."),
        .pokemonScale = 256,
        .pokemonOffset = 3,
        .trainerScale = 257,
        .trainerOffset = -1,
        .frontPic = gMonFrontPic_DoduoHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 56) : MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE_SLOW,
        .backPic = gMonBackPic_DoduoHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 8 : 6,
        .backAnimId = BACK_ANIM_TRIANGLE_DOWN,
        .palette = gMonPalette_DoduoHoenn,
        .shinyPalette = gMonShinyPalette_DoduoHoenn,
        .iconSprite = gMonIcon_Doduo,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 9, SHADOW_SIZE_M)
        FOOTPRINT(Doduo)
        OVERWORLD(
            sPicTable_Doduo,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Doduo,
            gShinyOverworldPalette_Doduo
        )
        .isSkyBattleBanned = B_SKY_BATTLE_STRICT_ELIGIBILITY,
        .levelUpLearnset = sDoduoHoennLevelUpLearnset,
        .teachableLearnset = sDoduoTeachableLearnset,
        .eggMoveLearnset = sDoduoEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 31, SPECIES_DODRIO_HOENN}),
    },

    [SPECIES_DODRIO_HOENN] =
    {
        .baseHP        = 90,
        .baseAttack    = 130,
        .baseDefense   = 80,
        .baseSpeed     = 100,
        .baseSpAttack  = 50,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_DARK, TYPE_POISON),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_7
        .expYield = 165,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 161,
    #else
        .expYield = 158,
    #endif
        .evYield_Attack = 2,
        .itemRare = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_MOODY, ABILITY_BIG_PECKS, ABILITY_DRAGONS_MAW },
        .bodyColor = BODY_COLOR_BROWN,
        .noFlip = TRUE,
        .speciesName = _("Dodrio"),
        .cryId = CRY_DODRIO,
        .natDexNum = NATIONAL_DEX_DODRIO,
        .categoryName = _("Triple Bird"),
        .height = 18,
        .weight = 852,
        .description = COMPOUND_STRING(
            "An highly aggressive predator that hunts in\n"
            "shallows. While two of its heads constantly\n"
            "hiss and argue, the third head silently watches\n"
            "for any opening to deliver a lethal, venomous bite."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 268,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_DodrioHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_LUNGE_GROW : ANIM_V_STRETCH,
        .backPic = gMonBackPic_DodrioHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 1 : 3,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_DodrioHoenn,
        .shinyPalette = gMonShinyPalette_DodrioHoenn,
        .iconSprite = gMonIcon_Dodrio,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 12, SHADOW_SIZE_L)
        FOOTPRINT(Dodrio)
        OVERWORLD(
            sPicTable_Dodrio,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Dodrio,
            gShinyOverworldPalette_Dodrio
        )
        .isSkyBattleBanned = B_SKY_BATTLE_STRICT_ELIGIBILITY,
        .levelUpLearnset = sDodrioHoennLevelUpLearnset,
        .teachableLearnset = sDodrioTeachableLearnset,
    },
	
	[SPECIES_SKARMORY_HOENN] =
    {
        .baseHP        = 65,
        .baseAttack    = 80,
        .baseDefense   = 140,
        .baseSpeed     = 70,
        .baseSpAttack  = 40,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_STEEL, TYPE_FLYING),
        .catchRate = 25,
        .expYield = 163,
        .evYield_Defense = 2,
        .itemRare = ITEM_METAL_COAT,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_LEVITATE, ABILITY_FLAME_BODY, ABILITY_WEAK_ARMOR },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Skarmory"),
        .cryId = CRY_SKARMORY,
        .natDexNum = NATIONAL_DEX_SKARMORY,
        .categoryName = _("Armor Bird"),
        .height = 17,
        .weight = 505,
        .description = COMPOUND_STRING(
            "Its steel wings glow red-hot from an internal\n"
            "blaze. It swoops down from volcanic peaks\n"
            "at blinding speeds, melting its targets with\n"
            "the sheer, intense heat of its passage."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 271,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_SkarmoryHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 0 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_STRETCH : ANIM_V_SHAKE,
        .backPic = gMonBackPic_SkarmoryHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(48, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 1,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_SkarmoryHoenn,
        .shinyPalette = gMonShinyPalette_SkarmoryHoenn,
        .iconSprite = gMonIcon_Skarmory,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 9, SHADOW_SIZE_M)
        FOOTPRINT(Skarmory)
        OVERWORLD(
            sPicTable_Skarmory,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Skarmory,
            gShinyOverworldPalette_Skarmory
        )
        .levelUpLearnset = sSkarmoryHoennLevelUpLearnset,
        .teachableLearnset = sSkarmoryTeachableLearnset,
        .eggMoveLearnset = sSkarmoryEggMoveLearnset,
    },
	
	[SPECIES_PSYDUCK_HOENN] =
    {
        .baseHP        = 50,
        .baseAttack    = 75,
        .baseDefense   = 43,
        .baseSpeed     = 65,
        .baseSpAttack  = 52,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 190,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 64 : 80,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_FUR_COAT, ABILITY_ANALYTIC },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Psyduck"),
        .cryId = CRY_PSYDUCK,
        .natDexNum = NATIONAL_DEX_PSYDUCK,
        .categoryName = _("Duck"),
        .height = 8,
        .weight = 196,
        .description = COMPOUND_STRING(
            "It is highly suspicious and suffers no\n"
            "headaches. It slinks through dark alleyways,\n"
            "always plotting minor mischief while\n"
            "hiding its face from passersby."),
        .pokemonScale = 369,
        .pokemonOffset = 15,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_PsyduckHoenn,
        .frontPicSize = MON_COORDS_SIZE(40, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_JUMPS_H_JUMPS,
        .backPic = gMonBackPic_PsyduckHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 56) : MON_COORDS_SIZE(48, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 0,
        .backAnimId = BACK_ANIM_H_SLIDE,
        .palette = gMonPalette_PsyduckHoenn,
        .shinyPalette = gMonShinyPalette_PsyduckHoenn,
        .iconSprite = gMonIcon_Psyduck,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(1, 10, SHADOW_SIZE_M)
        FOOTPRINT(Psyduck)
        OVERWORLD(
            sPicTable_Psyduck,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Psyduck,
            gShinyOverworldPalette_Psyduck
        )
        .levelUpLearnset = sPsyduckHoennLevelUpLearnset,
        .teachableLearnset = sPsyduckTeachableLearnset,
        .eggMoveLearnset = sPsyduckEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_SHYDUCK}),
    },
	
	[SPECIES_SHYDUCK] =
    {
        .baseHP        = 90,
        .baseAttack    = 86,
        .baseDefense   = 86,
        .baseSpeed     = 86,
        .baseSpAttack  = 86,
        .baseSpDefense = 86,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 75,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 175 : 174,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
        .abilities = { ABILITY_ANGER_POINT, ABILITY_FUR_COAT, ABILITY_ANALYTIC },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Shyduck"),
        .cryId = CRY_GOLDUCK,
        .natDexNum = NATIONAL_DEX_GOLDUCK,
        .categoryName = _("Duck"),
        .height = 17,
        .weight = 766,
        .description = COMPOUND_STRING(
            "It covers its eyes with long, dark feathers\n"
            "to avoid attention. Though it appears timid,\n"
            "it is actually studying its surroundings\n"
            "from the safety of the shadows."),
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 273,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_Shyduck,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 2 : 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE_SLOW,
        .backPic = gMonBackPic_Shyduck,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 3,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Shyduck,
        .shinyPalette = gMonShinyPalette_Shyduck,
        .iconSprite = gMonIcon_Golduck,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 7, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Golduck)
        OVERWORLD(
            sPicTable_Golduck,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Golduck,
            gShinyOverworldPalette_Golduck
        )
        .levelUpLearnset = sShyduckLevelUpLearnset,
        .teachableLearnset = sGolduckTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_SLYDUCK}),
    },
	
	[SPECIES_SLYDUCK] =
    {
        .baseHP        = 80,
        .baseAttack    = 156,
        .baseDefense   = 70,
        .baseSpeed     = 128,
        .baseSpAttack  = 96,
        .baseSpDefense = 70,
        .types = MON_TYPES(TYPE_DARK),
        .catchRate = 75,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 175 : 174,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_DARK_AURA, ABILITY_ANALYTIC},
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Slyduck"),
        .cryId = CRY_GOLDUCK,
        .natDexNum = NATIONAL_DEX_GOLDUCK,
        .categoryName = _("Duck"),
        .height = 17,
        .weight = 766,
        .description = COMPOUND_STRING(
            "A master of stealth that moves without\n"
            "making a sound. It drapes its dark cloak\n"
            "around itself to blend into the night,\n"
            "swiping valuables from unsuspecting foes."),
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 273,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_Slyduck,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 2 : 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE_SLOW,
        .backPic = gMonBackPic_Slyduck,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 3,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Slyduck,
        .shinyPalette = gMonShinyPalette_Slyduck,
        .iconSprite = gMonIcon_Golduck,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 6, SHADOW_SIZE_M)
        FOOTPRINT(Golduck)
        OVERWORLD(
            sPicTable_Golduck,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Golduck,
            gShinyOverworldPalette_Golduck
        )
        .levelUpLearnset = sSlyduckLevelUpLearnset,
        .teachableLearnset = sGolduckTeachableLearnset,
    },
	
	[SPECIES_GROWLITHE_HOENN] =
    {
        .baseHP        = 55,
        .baseAttack    = 60,
        .baseDefense   = 65,
        .baseSpeed     = 60,
        .baseSpAttack  = 50,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GRASS),
        .catchRate = 190,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 70 : 91,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_STENCH, ABILITY_FLASH_FIRE, ABILITY_INTIMIDATE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Growlithe"),
        .cryId = CRY_GROWLITHE,
        .natDexNum = NATIONAL_DEX_GROWLITHE,
        .categoryName = _("Puppy"),
        .height = 7,
        .weight = 190,
        .description = COMPOUND_STRING(
            "It lives in dense forests prone to wildfires.\n"
            "Its bark-like skin is entirely fireproof. It\n"
            "gathers dried brush along its mane and tail,\n"
            "igniting it into bright flames to deter foes."),
        .pokemonScale = 346,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GrowlitheHoenn,
        .frontPicSize = MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_BACK_AND_LUNGE : ANIM_V_STRETCH,
        .frontAnimDelay = 30,
        .backPic = gMonBackPic_GrowlitheHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(48, 56),
        .backPicYOffset = 8,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_GrowlitheHoenn,
        .shinyPalette = gMonShinyPalette_GrowlitheHoenn,
        .iconSprite = gMonIcon_Growlithe,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 0 : 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(0, 14, SHADOW_SIZE_M)
        FOOTPRINT(Growlithe)
        OVERWORLD(
            sPicTable_Growlithe,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Growlithe,
            gShinyOverworldPalette_Growlithe
        )
        .levelUpLearnset = sGrowlitheHoennLevelUpLearnset,
        .teachableLearnset = sGrowlitheTeachableLearnset,
        .eggMoveLearnset = sGrowlitheEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 35, SPECIES_ARCANINE_HOENN}),
    },

    [SPECIES_ARCANINE_HOENN] =
    {
        .baseHP        = 90,
        .baseAttack    = 115,
        .baseDefense   = 90,
        .baseSpeed     = 110,
        .baseSpAttack  = 105,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GRASS),
        .catchRate = 75,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 194 : 213,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(25),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_STENCH, ABILITY_FLASH_FIRE, ABILITY_INTIMIDATE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Arcanine"),
        .cryId = CRY_ARCANINE,
        .natDexNum = NATIONAL_DEX_ARCANINE,
        .categoryName = _("Legendary"),
        .height = 19,
        .weight = 1550,
        .description = COMPOUND_STRING(
            "An majestic protector of the woodlands. It runs\n"
            "at breathtaking speeds, leaving a trail of\n"
            "glowing embers in its wake. It controls the\n"
            "intense flames on its body to avoid burning trees."),
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 312,
        .trainerOffset = 4,
        .frontPic = gMonFrontPic_ArcanineHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_H_VIBRATE : ANIM_V_SHAKE,
        .frontAnimDelay = P_GBA_STYLE_SPECIES_GFX ? 40 : 8,
        .backPic = gMonBackPic_ArcanineHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 6 : 4,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_ArcanineHoenn,
        .shinyPalette = gMonShinyPalette_ArcanineHoenn,
        .iconSprite = gMonIcon_Arcanine,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 0 : 3,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-4, 11, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Arcanine)
        OVERWORLD(
            sPicTable_Arcanine,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Arcanine,
            gShinyOverworldPalette_Arcanine
        )
        .levelUpLearnset = sArcanineHoennLevelUpLearnset,
        .teachableLearnset = sArcanineTeachableLearnset,
    },
	
	[SPECIES_WEEDLE_HOENN] =
    {
        .baseHP        = 40,
        .baseAttack    = 35,
        .baseDefense   = 30,
        .baseSpeed     = 50,
        .baseSpAttack  = 20,
        .baseSpDefense = 20,
        .types = MON_TYPES(TYPE_ICE, TYPE_POISON),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 39 : 52,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_COMPOUND_EYES, ABILITY_OVERCOAT, ABILITY_RUN_AWAY },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Weedle"),
        .cryId = CRY_WEEDLE,
        .natDexNum = NATIONAL_DEX_WEEDLE,
        .categoryName = _("Hairy Bug"),
        .height = 3,
        .weight = 32,
        .description = COMPOUND_STRING(
            "It inhabits snow-covered forests. The sharp\n"
            "horn on its head is made of pure, toxic ice.\n"
            "If stepped on, it breaks off inside the foe's\n"
            "foot, injecting a freezing, numbing venom."),
        .pokemonScale = 455,
        .pokemonOffset = 22,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_WeedleHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 32) : MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 18 : 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SLIDE_SLOW,
        .frontAnimDelay = 10,
        .backPic = gMonBackPic_WeedleHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 48) : MON_COORDS_SIZE(56, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 7,
        .backAnimId = BACK_ANIM_H_SLIDE,
        .palette = gMonPalette_WeedleHoenn,
        .shinyPalette = gMonShinyPalette_WeedleHoenn,
        .iconSprite = gMonIcon_Weedle,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(0, 0, SHADOW_SIZE_S)
        FOOTPRINT(Weedle)
        OVERWORLD(
            sPicTable_Weedle,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SPOT,
            sAnimTable_Following,
            gOverworldPalette_Weedle,
            gShinyOverworldPalette_Weedle
        )
        .teachingType = TM_ILLITERATE,
        .levelUpLearnset = sWeedleHoennLevelUpLearnset,
        .teachableLearnset = sWeedleTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 7, SPECIES_KAKUNA_HOENN}),
    },

    [SPECIES_KAKUNA_HOENN] =
    {
        .baseHP        = 45,
        .baseAttack    = 25,
        .baseDefense   = 50,
        .baseSpeed     = 35,
        .baseSpAttack  = 25,
        .baseSpDefense = 25,
        .types = MON_TYPES(TYPE_ICE, TYPE_POISON),
        .catchRate = 120,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 72 : 71,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SHED_SKIN, ABILITY_SHELL_ARMOR, ABILITY_OVERCOAT },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Kakuna"),
        .cryId = CRY_KAKUNA,
        .natDexNum = NATIONAL_DEX_KAKUNA,
        .categoryName = _("Cocoon"),
        .height = 6,
        .weight = 100,
        .description = COMPOUND_STRING(
            "While awaiting evolution, its shell becomes\n"
            "reinforced by layers of solid frost. It remains\n"
            "motionless beneath snowdrifts, secreting a\n"
            "highly toxic slurry to keep its core from freezing."),
        .pokemonScale = 424,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_KakunaHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 40) : MON_COORDS_SIZE(24, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 14 : 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GLOW_ORANGE,
        .frontAnimDelay = 20,
        .backPic = gMonBackPic_KakunaHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 48) : MON_COORDS_SIZE(32, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 10 : 12,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_KakunaHoenn,
        .shinyPalette = gMonShinyPalette_KakunaHoenn,
        .iconSprite = gMonIcon_Kakuna,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(-3, 3, SHADOW_SIZE_S)
        FOOTPRINT(Kakuna)
        OVERWORLD(
            sPicTable_Kakuna,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SPOT,
            sAnimTable_Following,
            gOverworldPalette_Kakuna,
            gShinyOverworldPalette_Kakuna
        )
        .teachingType = TM_ILLITERATE,
        .levelUpLearnset = sKakunaHoennLevelUpLearnset,
        .teachableLearnset = sKakunaTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 10, SPECIES_BEEDRILL_HOENN}),
    },

    [SPECIES_BEEDRILL_HOENN] =
    {
        .baseHP        = 65,
        .baseAttack    = 110,
        .baseDefense   = 40,
        .baseSpeed     = 135,
        .baseSpAttack  = 45,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_ICE, TYPE_POISON),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 198,
    #elif P_UPDATED_EXP_YIELDS >= GEN_6
        .expYield = 178,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 173,
    #else
        .expYield = 159,
    #endif
        .evYield_Attack = 2,
        .evYield_SpDefense = 1,
        .itemRare = ITEM_POISON_BARB,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_SLUSH_RUSH, ABILITY_SKILL_LINK, ABILITY_LEVITATE },
        .bodyColor = BODY_COLOR_YELLOW,
        .speciesName = _("Beedrill"),
        .cryId = CRY_BEEDRILL,
        .natDexNum = NATIONAL_DEX_BEEDRILL,
        .categoryName = _("Poison Bee"),
        .height = 10,
        .weight = 295,
        .description = COMPOUND_STRING(
            "It flies on wings of frozen crystal, buzzing\n"
            "through blizzards at high speeds. It uses its\n"
            "twin icicle lances to stab foes repeatedly,\n"
            "instantly freezing and poisoning their bodies."),
        .pokemonScale = 366,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_BeedrillHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 48) : MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 5,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_H_VIBRATE : ANIM_ZIGZAG_SLOW,
        .enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 8 : 9,
        .backPic = gMonBackPic_BeedrillHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 48) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 5,
        .backAnimId = BACK_ANIM_H_VIBRATE,
        .palette = gMonPalette_BeedrillHoenn,
        .shinyPalette = gMonShinyPalette_BeedrillHoenn,
        .iconSprite = gMonIcon_Beedrill,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 15, SHADOW_SIZE_M)
        FOOTPRINT(Beedrill)
        OVERWORLD(
            sPicTable_Beedrill,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Beedrill,
            gShinyOverworldPalette_Beedrill
        )
        .levelUpLearnset = sBeedrillHoennLevelUpLearnset,
        .teachableLearnset = sBeedrillTeachableLearnset,
    },
	
	[SPECIES_BELLSPROUT_HOENN] =
    {
        .baseHP        = 66,
        .baseAttack    = 46,
        .baseDefense   = 62,
        .baseSpeed     = 42,
        .baseSpAttack  = 46,
        .baseSpDefense = 58,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ICE),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 60 : 84,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_SAP_SIPPER, ABILITY_SNOW_CLOAK, ABILITY_GLUTTONY },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Bellsprout"),
        .cryId = CRY_BELLSPROUT,
        .natDexNum = NATIONAL_DEX_BELLSPROUT,
        .categoryName = _("Flower"),
        .height = 7,
        .weight = 40,
        .description = COMPOUND_STRING(
            "It anchors its roots in deep snow to mimic a\n"
            "withered bud. Instead of corrosive acid,\n"
            "its mouth spits a sub-zero liquid that\n"
            "instantly freezes small bug Pokémon solid."),
        .pokemonScale = 354,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_BellsproutHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 15 : 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_STRETCH : ANIM_H_JUMPS,
        .backPic = gMonBackPic_BellsproutHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(40, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 10 : 11,
        .backAnimId = BACK_ANIM_V_STRETCH,
        .palette = gMonPalette_BellsproutHoenn,
        .shinyPalette = gMonShinyPalette_BellsproutHoenn,
        .iconSprite = gMonIcon_Bellsprout,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-2, 3, SHADOW_SIZE_S)
        FOOTPRINT(Bellsprout)
        OVERWORLD(
            sPicTable_Bellsprout,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Bellsprout,
            gShinyOverworldPalette_Bellsprout
        )
        .levelUpLearnset = sBellsproutHoennLevelUpLearnset,
        .teachableLearnset = sBellsproutTeachableLearnset,
        .eggMoveLearnset = sBellsproutEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 21, SPECIES_WEEPINBELL_HOENN}),
    },

    [SPECIES_WEEPINBELL_HOENN] =
    {
        .baseHP        = 91,
        .baseAttack    = 78,
        .baseDefense   = 91,
        .baseSpeed     = 42,
        .baseSpAttack  = 47,
        .baseSpDefense = 69,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ICE),
        .catchRate = 120,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 137 : 151,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_SAP_SIPPER, ABILITY_ICE_BODY, ABILITY_GLUTTONY },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("Weepinbell"),
        .cryId = CRY_WEEPINBELL,
        .natDexNum = NATIONAL_DEX_WEEPINBELL,
        .categoryName = _("Flycatcher"),
        .height = 10,
        .weight = 64,
        .description = COMPOUND_STRING(
            "The jagged ice coating its rim is sharp enough\n"
            "to slice through frozen branches. It traps\n"
            "freezing air inside its body, keeping captured\n"
            "prey fresh beneath a layer of solid frost."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_WeepinbellHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 48),
        .frontPicYOffset = 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_SWING_CONVEX,
        .frontAnimDelay = 3,
        .backPic = gMonBackPic_WeepinbellHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 11,
        .backAnimId = BACK_ANIM_V_STRETCH,
        .palette = gMonPalette_WeepinbellHoenn,
        .shinyPalette = gMonShinyPalette_WeepinbellHoenn,
        .iconSprite = gMonIcon_Weepinbell,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-3, 3, SHADOW_SIZE_M)
        FOOTPRINT(Weepinbell)
        OVERWORLD(
            sPicTable_Weepinbell,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SPOT,
            sAnimTable_Following,
            gOverworldPalette_Weepinbell,
            gShinyOverworldPalette_Weepinbell
        )
        .levelUpLearnset = sWeepinbellHoennLevelUpLearnset,
        .teachableLearnset = sWeepinbellTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 36, SPECIES_VICTREEBEL_HOENN}),
    },

#if P_UPDATED_STATS >= GEN_6
    #define VICTREEBEL_SP_DEF 70
#elif P_UPDATED_STATS >= GEN_2
    #define VICTREEBEL_SP_DEF 60
#else
    #define VICTREEBEL_SP_DEF 100
#endif

    [SPECIES_VICTREEBEL_HOENN] =
    {
        .baseHP        = 106,
        .baseAttack    = 96,
        .baseDefense   = 112,
        .baseSpeed     = 51,
        .baseSpAttack  = 76,
        .baseSpDefense = 89,
        .types = MON_TYPES(TYPE_GRASS, TYPE_ICE),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 245,
    #elif P_UPDATED_EXP_YIELDS >= GEN_6
        .expYield = 221,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 216,
    #else
        .expYield = 191,
    #endif
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_SAP_SIPPER, ABILITY_ICE_BODY, ABILITY_GLUTTONY },
        .bodyColor = BODY_COLOR_GREEN,
        .noFlip = TRUE,
        .speciesName = _("Victreebel"),
        .cryId = CRY_VICTREEBEL,
        .natDexNum = NATIONAL_DEX_VICTREEBEL,
        .categoryName = _("Flycatcher"),
        .height = 17,
        .weight = 155,
        .description = COMPOUND_STRING(
            "Its giant, ice-capped mouth produces a sweet,\n"
            "chilled nectar to lure prey into its maw.\n"
            "Once a target slips inside, it is instantly\n"
            "flash-frozen by a pool of sub-zero sap."),
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 312,
        .trainerOffset = 3,
        .frontPic = gMonFrontPic_VictreebelHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_JUMPS_V_STRETCH,
        .backPic = gMonBackPic_VictreebelHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_V_STRETCH,
        .palette = gMonPalette_VictreebelHoenn,
        .shinyPalette = gMonShinyPalette_VictreebelHoenn,
        .iconSprite = gMonIcon_Victreebel,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 8, SHADOW_SIZE_M)
        FOOTPRINT(Victreebel)
        OVERWORLD(
            sPicTable_Victreebel,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SPOT,
            sAnimTable_Following,
            gOverworldPalette_Victreebel,
            gShinyOverworldPalette_Victreebel
        )
        .levelUpLearnset = sVictreebelLevelUpLearnset,
        .teachableLearnset = sVictreebelTeachableLearnset,
    },
	
	[SPECIES_CLEFFA_HOENN] =
    {
        .baseHP        = 50,
        .baseAttack    = 15,
        .baseDefense   = 28,
        .baseSpeed     = 15,
        .baseSpAttack  = 55,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 150,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 44 : 37,
        .evYield_SpDefense = 1,
        .itemRare = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
        .friendship = 140,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_SOLID_ROCK, ABILITY_MAGIC_GUARD, ABILITY_FRIEND_GUARD },
    #else
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FRIEND_GUARD },
    #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = TRUE,
        .speciesName = _("Cleffa"),
        .cryId = CRY_CLEFFA,
        .natDexNum = NATIONAL_DEX_CLEFFA,
        .categoryName = _("Star Shape"),
        .height = 3,
        .weight = 30,
        .description = COMPOUND_STRING(
            "Its dense, stone-like body is believed to\n"
            "be a piece of a fallen meteorite. On nights\n"
            "with a clear sky, the colorful crystals on\n"
            "its ears glow with a strange cosmic light."),
        .pokemonScale = 462,
        .pokemonOffset = 23,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CleffaHoenn,
        .frontPicSize = MON_COORDS_SIZE(32, 32),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 20 : 18,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_JUMPS_SMALL,
        .backPic = gMonBackPic_CleffaHoenn,
        .backPicSize = MON_COORDS_SIZE(48, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 15 : 13,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_CleffaHoenn,
        .shinyPalette = gMonShinyPalette_CleffaHoenn,
        .iconSprite = gMonIcon_Cleffa,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(0, -4, SHADOW_SIZE_S)
        FOOTPRINT(Cleffa)
        OVERWORLD(
            sPicTable_Cleffa,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Cleffa,
            gShinyOverworldPalette_Cleffa
        )
        .levelUpLearnset = sCleffaHoennLevelUpLearnset,
        .teachableLearnset = sCleffaTeachableLearnset,
        .eggMoveLearnset = sCleffaEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_CLEFAIRY_HOENN, CONDITIONS({IF_MIN_FRIENDSHIP, FRIENDSHIP_EVO_THRESHOLD})}),
    },

    [SPECIES_CLEFAIRY_HOENN] =
    {
        .baseHP        = 70,
        .baseAttack    = 20,
        .baseDefense   = 50,
        .baseSpeed     = 40,
        .baseSpAttack  = 70,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 150,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 113 : 68,
        .evYield_HP = 2,
        .itemRare = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
        .friendship = 140,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_SOLID_ROCK, ABILITY_MAGIC_GUARD, ABILITY_FRIEND_GUARD },
    #else
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_FRIEND_GUARD },
    #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = TRUE,
        .speciesName = _("Clefairy"),
        .cryId = CRY_CLEFAIRY,
        .natDexNum = NATIONAL_DEX_CLEFAIRY,
        .categoryName = _("Fairy"),
        .height = 6,
        .weight = 75,
        .description = COMPOUND_STRING(
            "It lives deep inside dark mountain caves,\n"
            "using the glowing gems on its back to see.\n"
            "When it dances beneath a full moon, its\n"
            "crystals refract the moonlight beautifully."),
        .pokemonScale = 441,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ClefairyHoenn,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 16 : 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ClefairyHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(56, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 14,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_ClefairyHoenn,
        .shinyPalette = gMonShinyPalette_ClefairyHoenn,
        .iconSprite = gMonIcon_Clefairy,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(1, 1, SHADOW_SIZE_S)
        FOOTPRINT(Clefairy)
        OVERWORLD(
            sPicTable_Clefairy,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Clefairy,
            gShinyOverworldPalette_Clefairy
        )
        .levelUpLearnset = sClefairyHoennLevelUpLearnset,
        .teachableLearnset = sClefairyTeachableLearnset,
        .evolutions = EVOLUTION({EVO_ITEM, ITEM_MOON_STONE, SPECIES_CLEFABLE_HOENN}),
    },

    [SPECIES_CLEFABLE_HOENN] =
    {
        .baseHP        = 95,
        .baseAttack    = 50,
        .baseDefense   = 83,
        .baseSpeed     = 75,
        .baseSpAttack  = 115,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 25,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 242,
    #elif P_UPDATED_EXP_YIELDS >= GEN_6
        .expYield = 217,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 213,
    #else
        .expYield = 129,
    #endif
        .evYield_HP = 3,
        .itemRare = ITEM_MOON_STONE,
        .genderRatio = PERCENT_FEMALE(75),
        .eggCycles = 10,
        .friendship = 140,
        .growthRate = GROWTH_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FAIRY),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_SOLID_ROCK, ABILITY_MAGIC_GUARD, ABILITY_FRIEND_GUARD },
    #else
        .abilities = { ABILITY_CUTE_CHARM, ABILITY_NONE, ABILITY_UNAWARE },
    #endif
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = TRUE,
        .speciesName = _("Clefable"),
        .cryId = CRY_CLEFABLE,
        .natDexNum = NATIONAL_DEX_CLEFABLE,
        .categoryName = _("Fairy"),
        .height = 13,
        .weight = 400,
        .description = COMPOUND_STRING(
            "A rare Pokémon whose rocky body is filled \n"
            "with brilliant geodes. The massive crystals\n"
            "on its back can store cosmic energy, allowing\n"
            "it to levitate despite its immense weight."),
        .pokemonScale = 256,
        .pokemonOffset = 5,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ClefableHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 8 : 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL_SLOW : ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_ClefableHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 48) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 10,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_ClefableHoenn,
        .shinyPalette = gMonShinyPalette_ClefableHoenn,
        .iconSprite = gMonIcon_Clefable,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 11, SHADOW_SIZE_M)
        FOOTPRINT(Clefable)
        OVERWORLD(
            sPicTable_Clefable,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Clefable,
            gShinyOverworldPalette_Clefable
        )
        .levelUpLearnset = sClefableHoennLevelUpLearnset,
        .teachableLearnset = sClefableTeachableLearnset,
    },
	
	[SPECIES_SEEL_HOENN] =
    {
        .baseHP        = 63,
        .baseAttack    = 66,
        .baseDefense   = 55,
        .baseSpeed     = 65,
        .baseSpAttack  = 66,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_ICE, TYPE_DRAGON),
        .catchRate = 190,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 65 : 100,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_SLUSH_RUSH, ABILITY_UNAWARE, ABILITY_DRAGONIZE },
    #else
        .abilities = { ABILITY_THICK_FAT, ABILITY_NONE, ABILITY_ICE_BODY },
    #endif
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Seel"),
        .cryId = CRY_SEEL,
        .natDexNum = NATIONAL_DEX_SEEL,
        .categoryName = _("Sea Lion"),
        .height = 11,
        .weight = 900,
        .description = COMPOUND_STRING(
            "It lives in frigid, iceberg-filled seas.\n"
            "Its sharp fangs and icicle horn contain\n"
            "draconic energy, allowing it to easily\n"
            "shatter thick sheets of ice when swimming."),
        .pokemonScale = 297,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SeelHoenn,
        .frontPicSize = MON_COORDS_SIZE(56, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 10 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_SWING_CONCAVE : ANIM_H_SLIDE_SLOW,
        .backPic = gMonBackPic_SeelHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(64, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 10 : 1,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_SeelHoenn,
        .shinyPalette = gMonShinyPalette_SeelHoenn,
        .iconSprite = gMonIcon_Seel,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(1, 12, SHADOW_SIZE_L)
        FOOTPRINT(Seel)
        OVERWORLD(
            sPicTable_Seel,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SLITHER,
            sAnimTable_Following,
            gOverworldPalette_Seel,
            gShinyOverworldPalette_Seel
        )
        .levelUpLearnset = sSeelHoennLevelUpLearnset,
        .teachableLearnset = sSeelTeachableLearnset,
        .eggMoveLearnset = sSeelEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 34, SPECIES_DEWGONG_HOENN}),
    },

    [SPECIES_DEWGONG_HOENN] =
    {
        .baseHP        = 78,
        .baseAttack    = 120,
        .baseDefense   = 66,
        .baseSpeed     = 120,
        .baseSpAttack  = 78,
        .baseSpDefense = 66,
        .types = MON_TYPES(TYPE_ICE, TYPE_DRAGON),
        .catchRate = 75,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 166 : 176,
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_SLUSH_RUSH, ABILITY_DRAGONS_MAW, ABILITY_DRAGONIZE },
    #else
        .abilities = { ABILITY_THICK_FAT, ABILITY_NONE, ABILITY_ICE_BODY },
    #endif
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Dewgong"),
        .cryId = CRY_DEWGONG,
        .natDexNum = NATIONAL_DEX_DEWGONG,
        .categoryName = _("Sea Lion"),
        .height = 17,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "Its body has elongated into a sleek, draconic\n"
            "shape to minimize drag. It coils through freezing\n"
            "waters at high speeds, using the glowing horn\n"
            "on its head to strike down prey instantly."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 275,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_DewgongHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .backPic = gMonBackPic_DewgongHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 3,
        .backAnimId = BACK_ANIM_H_SLIDE,
        .palette = gMonPalette_DewgongHoenn,
        .shinyPalette = gMonShinyPalette_DewgongHoenn,
        .iconSprite = gMonIcon_Dewgong,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 9, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Dewgong)
        OVERWORLD(
            sPicTable_Dewgong,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Dewgong,
            gShinyOverworldPalette_Dewgong
        )
        .levelUpLearnset = sDewgongHoennLevelUpLearnset,
        .teachableLearnset = sDewgongTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 50, SPECIES_BARIONG}),
    },
	
	[SPECIES_BARIONG] =
    {
        .baseHP        = 100,
        .baseAttack    = 100,
        .baseDefense   = 85,
        .baseSpeed     = 60,
        .baseSpAttack  = 140,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_ICE, TYPE_DRAGON),
        .catchRate = 75,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 166 : 176,
        .evYield_SpDefense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_1, EGG_GROUP_FIELD),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_MULTISCALE, ABILITY_DRAGONS_MAW, ABILITY_DRAGONIZE },
    #else
        .abilities = { ABILITY_THICK_FAT, ABILITY_NONE, ABILITY_ICE_BODY },
    #endif
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Bariong"),
        .cryId = CRY_DEWGONG,
        .natDexNum = NATIONAL_DEX_DEWGONG,
        .categoryName = _("Sea Lion"),
        .height = 17,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "A legendary tyrant of the frozen wastes.\n"
            "Its wings are made of solid, unbreakable\n"
            "glacier ice. It can trigger massive blizzards\n"
            "with a single roar, freezing entire lakes solid."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 275,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Bariong,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .backPic = gMonBackPic_Bariong,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 5,
        .backAnimId = BACK_ANIM_H_SLIDE,
        .palette = gMonPalette_Bariong,
        .shinyPalette = gMonShinyPalette_Bariong,
        .iconSprite = gMonIcon_Dewgong,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 9, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Dewgong)
        OVERWORLD(
            sPicTable_Dewgong,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Dewgong,
            gShinyOverworldPalette_Dewgong
        )
        .levelUpLearnset = sBariongLevelUpLearnset,
        .teachableLearnset = sDewgongTeachableLearnset,
    },
	
	[SPECIES_EXEGGCUTE_HOENN] =
    {
        .baseHP        = 60,
        .baseAttack    = 56,
        .baseDefense   = 55,
        .baseSpeed     = 20,
        .baseSpAttack  = 54,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 90,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 65 : 98,
        .evYield_Defense = 1,
        .itemRare = ITEM_PSYCHIC_SEED,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_GRASSY_SURGE, ABILITY_CHLOROPHYLL, ABILITY_PRANKSTER },
        .bodyColor = BODY_COLOR_PINK,
        .noFlip = TRUE,
        .speciesName = _("Exeggcute"),
        .cryId = CRY_EXEGGCUTE,
        .natDexNum = NATIONAL_DEX_EXEGGCUTE,
        .categoryName = _("Egg"),
        .height = 4,
        .weight = 25,
        .description = COMPOUND_STRING(
            "It hides by mimicking a clutch of common\n"
            "bird eggs to deceive predators. A tiny\n"
            "sprout grows from the leader's shell,\n"
            "bsorbing nutrients from rich soil."),
        .pokemonScale = 489,
        .pokemonOffset = -4,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ExeggcuteHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(56, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SLIDE_SLOW,
        .backPic = gMonBackPic_ExeggcuteHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(64, 32),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 2,
        .backAnimId = BACK_ANIM_H_SLIDE,
        .palette = gMonPalette_ExeggcuteHoenn,
        .shinyPalette = gMonShinyPalette_ExeggcuteHoenn,
        .iconSprite = gMonIcon_Exeggcute,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(1, -3, SHADOW_SIZE_L)
        FOOTPRINT(Exeggcute)
        OVERWORLD(
            sPicTable_Exeggcute,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SPOT,
            sAnimTable_Following,
            gOverworldPalette_Exeggcute,
            gShinyOverworldPalette_Exeggcute
        )
        .levelUpLearnset = sExeggcuteHoennLevelUpLearnset,
        .teachableLearnset = sExeggcuteTeachableLearnset,
        .eggMoveLearnset = sExeggcuteEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 32, SPECIES_EXEGGUTOR_HOENN}),
    },

    [SPECIES_EXEGGUTOR_HOENN] =
    {
        .baseHP        = 100,
        .baseAttack    = 60,
        .baseDefense   = 105,
        .baseSpeed     = 30,
        .baseSpAttack  = 130,
    #if P_UPDATED_STATS >= GEN_7
        .baseSpDefense = 105,
    #elif P_UPDATED_STATS >= GEN_2
        .baseSpDefense = 105,
    #else
        .baseSpDefense = 105,
    #endif
        .types = MON_TYPES(TYPE_GRASS, TYPE_NORMAL),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_7
        .expYield = 186,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 182,
    #else
        .expYield = 212,
    #endif
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_GRASS),
        .abilities = { ABILITY_GRASSY_SURGE, ABILITY_CHLOROPHYLL, ABILITY_STAMINA },
        .bodyColor = BODY_COLOR_YELLOW,
        .noFlip = TRUE,
        .speciesName = _("Exeggutor"),
        .cryId = CRY_EXEGGUTOR,
        .natDexNum = NATIONAL_DEX_EXEGGUTOR,
        .categoryName = _("Coconut"),
        .height = 20,
        .weight = 1200,
        .description = COMPOUND_STRING(
            "It looks like a beautifully grown tree.\n"
            "Lacking psychic power, it blends into\n"
            "normal forests perfectly. Its three main\n"
            "heads chatter merrily all day long."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 309,
        .trainerOffset = 5,
        .frontPic = gMonFrontPic_ExeggutorHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_JUMPS_V_STRETCH,
        .backPic = gMonBackPic_ExeggutorHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 0,
        .backAnimId = BACK_ANIM_CONCAVE_ARC_LARGE,
        .palette = gMonPalette_ExeggutorHoenn,
        .shinyPalette = gMonShinyPalette_ExeggutorHoenn,
        .iconSprite = gMonIcon_Exeggutor,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 13, SHADOW_SIZE_L)
        FOOTPRINT(Exeggutor)
        OVERWORLD(
            sPicTable_Exeggutor,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Exeggutor,
            gShinyOverworldPalette_Exeggutor
        )
        .levelUpLearnset = sExeggutorHoennLevelUpLearnset,
        .teachableLearnset = sExeggutorTeachableLearnset,
    },
	
	[SPECIES_SPEAROW_HOENN] =
    {
        .baseHP        = 45,
        .baseAttack    = 63,
        .baseDefense   = 39,
        .baseSpeed     = 68,
        .baseSpAttack  = 26,
        .baseSpDefense = 32,
        .types = MON_TYPES(TYPE_FIGHTING),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 52 : 58,
        .evYield_Speed = 1,
        .itemRare = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_KEEN_EYE, ABILITY_DEFIANT, ABILITY_ANGER_POINT },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Spearow"),
        .cryId = CRY_SPEAROW,
        .natDexNum = NATIONAL_DEX_SPEAROW,
        .categoryName = _("Tiny Bird"),
        .height = 3,
        .weight = 20,
        .description = COMPOUND_STRING(
            "Incapable of sustained flight, it has\n"
            "developed incredibly powerful legs. It\n"
            "relentlessly trains by kicking trees\n"
            "and charging headfirst into rocks."),
        .pokemonScale = 571,
        .pokemonOffset = 22,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SpearowHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 40) : MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 15 : 12,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_RISING_WOBBLE : ANIM_V_JUMPS_SMALL,
        .backPic = gMonBackPic_SpearowHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(56, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 12 : 6,
        .backAnimId = BACK_ANIM_TRIANGLE_DOWN,
        .palette = gMonPalette_SpearowHoenn,
        .shinyPalette = gMonShinyPalette_SpearowHoenn,
        .iconSprite = gMonIcon_Spearow,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 4, SHADOW_SIZE_S)
        FOOTPRINT(Spearow)
        OVERWORLD(
            sPicTable_Spearow,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Spearow,
            gShinyOverworldPalette_Spearow
        )
        .isSkyBattleBanned = B_SKY_BATTLE_STRICT_ELIGIBILITY,
        .levelUpLearnset = sSpearowHoennLevelUpLearnset,
        .teachableLearnset = sSpearowTeachableLearnset,
        .eggMoveLearnset = sSpearowEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_FEAROW_HOENN}),
    },

    [SPECIES_FEAROW_HOENN] =
    {
        .baseHP        = 85,
        .baseAttack    = 112,
        .baseDefense   = 85,
        .baseSpeed     = 98,
        .baseSpAttack  = 51,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_DARK),
        .catchRate = 90,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 155 : 162,
        .evYield_Speed = 2,
        .itemRare = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_ANGER_POINT, ABILITY_DEFIANT, ABILITY_RECKLESS },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Fearow"),
        .cryId = CRY_FEAROW,
        .natDexNum = NATIONAL_DEX_FEAROW,
        .categoryName = _("Beak"),
        .height = 12,
        .weight = 380,
        .description = COMPOUND_STRING(
            "It stalks its prey from the shadows\n"
            "rather than from the air. It strikes\n"
            "viciously without warning, using its\n"
            "long beak to target vital blind spots."),
        .pokemonScale = 278,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_FearowHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_FIGURE_8,
        .frontAnimDelay = 2,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_FearowHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 4,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_FearowHoenn,
        .shinyPalette = gMonShinyPalette_FearowHoenn,
        .iconSprite = gMonIcon_Fearow,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(11, 13, SHADOW_SIZE_M)
        FOOTPRINT(Fearow)
        OVERWORLD(
            sPicTable_Fearow,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Fearow,
            gShinyOverworldPalette_Fearow
        )
        .levelUpLearnset = sFearowHoennLevelUpLearnset,
        .teachableLearnset = sFearowTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_TERROW})
    },
	
	[SPECIES_TERROW] =
    {
        .baseHP        = 105,
        .baseAttack    = 132,
        .baseDefense   = 95,
        .baseSpeed     = 108,
        .baseSpAttack  = 51,
        .baseSpDefense = 51,
        .types = MON_TYPES(TYPE_FIGHTING, TYPE_DARK),
        .catchRate = 90,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 155 : 162,
        .evYield_Speed = 2,
        .itemRare = ITEM_SHARP_BEAK,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FLYING),
        .abilities = { ABILITY_ANGER_POINT, ABILITY_DEFIANT, ABILITY_RECKLESS },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Terrow"),
        .cryId = CRY_FEAROW,
        .natDexNum = NATIONAL_DEX_FEAROW,
        .categoryName = _("Beak"),
        .height = 12,
        .weight = 380,
        .description = COMPOUND_STRING(
            "Known as the tyrant of the plains, it\n"
            "intimidates rivals with its massive,\n"
            "vibrant crest. It ruthlessly hunts down\n"
            "anything that crosses its territory."),
        .pokemonScale = 278,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Terrow,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SLIDE_SHRINK,
        .frontAnimDelay = 2,
        .enemyMonElevation = 0,
        .backPic = gMonBackPic_Terrow,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 4,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_Terrow,
        .shinyPalette = gMonShinyPalette_Terrow,
        .iconSprite = gMonIcon_Fearow,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(12, 14, SHADOW_SIZE_L)
        FOOTPRINT(Fearow)
        OVERWORLD(
            sPicTable_Fearow,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Fearow,
            gShinyOverworldPalette_Fearow
        )
        .levelUpLearnset = sTerrowLevelUpLearnset,
        .teachableLearnset = sFearowTeachableLearnset,
    },
	
	[SPECIES_KRABBY_HOENN] =
    {
        .baseHP        = 45,
        .baseAttack    = 38,
        .baseDefense   = 48,
        .baseSpeed     = 34,
        .baseSpAttack  = 97,
        .baseSpDefense = 88,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = 225,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 65 : 115,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_SERENE_GRACE, ABILITY_SHELL_ARMOR, ABILITY_MAGIC_GUARD },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Krabby"),
        .cryId = CRY_KRABBY,
        .natDexNum = NATIONAL_DEX_KRABBY,
        .categoryName = _("River Crab"),
        .height = 4,
        .weight = 65,
        .description = COMPOUND_STRING(
            "It lives on beaches touched by starlight.\n"
            "The inner curves of its pincers contain a\n"
            "swirling, star-filled void. It snaps its\n"
            "claws to create localized psychic distortions."),
        .pokemonScale = 469,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = 0,
		.enemyMonElevation = 10,
        .frontPic = gMonFrontPic_KrabbyHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(64, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 9,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_H_SLIDE : ANIM_H_SLIDE_SLOW,
        .backPic = gMonBackPic_KrabbyHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 10 : 15,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_KrabbyHoenn,
        .shinyPalette = gMonShinyPalette_KrabbyHoenn,
        .iconSprite = gMonIcon_Krabby,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(0, 11, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Krabby)
        OVERWORLD(
            sPicTable_Krabby,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following_Asym,
            gOverworldPalette_Krabby,
            gShinyOverworldPalette_Krabby
        )
        .levelUpLearnset = sKrabbyHoennLevelUpLearnset,
        .teachableLearnset = sKrabbyTeachableLearnset,
        .eggMoveLearnset = sKrabbyEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 28, SPECIES_KINGLER_HOENN}),
    },

    [SPECIES_KINGLER_HOENN] =
    {
        .baseHP        = 85,
        .baseAttack    = 60,
        .baseDefense   = 75,
        .baseSpeed     = 60,
        .baseSpAttack  = 115,
        .baseSpDefense = 115,
        .types = MON_TYPES(TYPE_PSYCHIC),
        .catchRate = 60,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 166 : 206,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_WATER_3),
        .abilities = { ABILITY_SERENE_GRACE, ABILITY_SHELL_ARMOR, ABILITY_MAGIC_GUARD },
        .bodyColor = BODY_COLOR_RED,
        .noFlip = TRUE,
        .speciesName = _("Kingler"),
        .cryId = CRY_KINGLER,
        .natDexNum = NATIONAL_DEX_KINGLER,
        .categoryName = _("Pincer"),
        .height = 13,
        .weight = 600,
        .description = COMPOUND_STRING(
            "Its shell reshapes into the likeness of a\n"
            "wizard's hat as its mind expands. By opening\n"
            "its massive, cosmic pincer, it unleashes a\n"
            "wave of telekinetic power to levitate prey."),
        .pokemonScale = 256,
        .pokemonOffset = 2,
        .trainerScale = 256,
        .trainerOffset = 0,
		.enemyMonElevation = 10,
        .frontPic = gMonFrontPic_KinglerHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 64) : MON_COORDS_SIZE(64, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 3 : 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_ZIGZAG_SLOW : ANIM_V_SHAKE_TWICE,
        .frontAnimDelay = P_GBA_STYLE_SPECIES_GFX ? 0 : 4,
        .backPic = gMonBackPic_KinglerHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 4 : 5,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_KinglerHoenn,
        .shinyPalette = gMonShinyPalette_KinglerHoenn,
        .iconSprite = gMonIcon_Kingler,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-2, 12, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Kingler)
        OVERWORLD(
            sPicTable_Kingler,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following_Asym,
            gOverworldPalette_Kingler,
            gShinyOverworldPalette_Kingler
        )
        .levelUpLearnset = sKinglerHoennLevelUpLearnset,
        .teachableLearnset = sKinglerTeachableLearnset,
    },
	
	[SPECIES_MUNCHLAX_HOENN] =
    {
        .baseHP        = 100,
        .baseAttack    = 27,
        .baseDefense   = 76,
        .baseSpeed     = 36,
        .baseSpAttack  = 67,
        .baseSpDefense = 84,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 50,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 78 : 94,
        .evYield_HP = 1,
        .itemCommon = ITEM_LEFTOVERS,
        .itemRare = ITEM_LEFTOVERS,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CLEAR_BODY, ABILITY_IMMUNITY, ABILITY_GOOEY },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Munchlax"),
        .cryId = CRY_MUNCHLAX,
        .natDexNum = NATIONAL_DEX_MUNCHLAX,
        .categoryName = _("Big Eater"),
        .height = 6,
        .weight = 1050,
        .description = COMPOUND_STRING(
            "Its body is composed entirely of pure water.\n"
            "It splashes around riverbanks, absorbing any\n"
            "organic matter it comes across. It can drink\n"
            "hundreds of gallons of water in a single day."),
        .pokemonScale = 422,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_MunchlaxHoenn,
        .frontPicSize = MON_COORDS_SIZE(48, 48),
        .frontPicYOffset = 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE_SLOW,
        .backPic = gMonBackPic_MunchlaxHoenn,
        .backPicSize = MON_COORDS_SIZE(48, 56),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_GROW,
        .palette = gMonPalette_MunchlaxHoenn,
        .shinyPalette = gMonShinyPalette_MunchlaxHoenn,
        .iconSprite = gMonIcon_Munchlax,
        .iconPalIndex = 3,
        .pokemonJumpType = PKMN_JUMP_TYPE_SLOW,
        SHADOW(-2, 6, SHADOW_SIZE_L)
        FOOTPRINT(Munchlax)
        OVERWORLD(
            sPicTable_Munchlax,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Munchlax,
            gShinyOverworldPalette_Munchlax
        )
        .levelUpLearnset = sMunchlaxHoennLevelUpLearnset,
        .teachableLearnset = sMunchlaxTeachableLearnset,
        .eggMoveLearnset = sMunchlaxEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_SNORLAX_HOENN}),
    },

    [SPECIES_SNORLAX_HOENN] =
    {
        .baseHP        = 196,
        .baseAttack    = 57,
        .baseDefense   = 82,
        .baseSpeed     = 36,
        .baseSpAttack  = 102,
        .baseSpDefense = 67,
        .types = MON_TYPES(TYPE_WATER),
        .catchRate = 25,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 189 : 154,
        .evYield_HP = 2,
        .itemCommon = ITEM_LEFTOVERS,
        .itemRare = ITEM_LEFTOVERS,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 40,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
        .abilities = { ABILITY_WATER_ABSORB, ABILITY_IMMUNITY, ABILITY_GOOEY },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Snorlax"),
        .cryId = CRY_SNORLAX,
        .natDexNum = NATIONAL_DEX_SNORLAX,
        .categoryName = _("Sleeping"),
        .height = 21,
        .weight = 4600,
        .description = COMPOUND_STRING(
            "A massive water elemental that spends most of\n"
            "its time asleep in deep lakes. Its gelatinous\n"
            "body ripples gently as it breathes. Small fish\n"
            "Pokémon frequently swim right through it."),
        .pokemonScale = 256,
        .pokemonOffset = 4,
        .trainerScale = 423,
        .trainerOffset = 11,
        .frontPic = gMonFrontPic_SnorlaxHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_SWING_CONCAVE : ANIM_V_STRETCH,
        .backPic = gMonBackPic_SnorlaxHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 48) : MON_COORDS_SIZE(64, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 2,
        .backAnimId = BACK_ANIM_DIP_RIGHT_SIDE,
        .palette = gMonPalette_SnorlaxHoenn,
        .shinyPalette = gMonShinyPalette_SnorlaxHoenn,
        .iconSprite = gMonIcon_Snorlax,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 3,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 7, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Snorlax)
        OVERWORLD(
            sPicTable_Snorlax,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Snorlax,
            gShinyOverworldPalette_Snorlax
        )
        .levelUpLearnset = sSnorlaxHoennLevelUpLearnset,
        .teachableLearnset = sSnorlaxTeachableLearnset,
        .eggMoveLearnset = sSnorlaxEggMoveLearnset,
    },
	
	[SPECIES_RATTATA_HOENN] =
    {
        .baseHP        = 35,
        .baseAttack    = 66,
        .baseDefense   = 40,
        .baseSpeed     = 62,
        .baseSpAttack  = 20,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_POISON),
        .catchRate = 255,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 51 : 57,
        .evYield_Speed = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_ANGER_POINT, ABILITY_POISON_TOUCH, ABILITY_STENCH },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("Rattata"),
        .cryId = CRY_RATTATA,
        .natDexNum = NATIONAL_DEX_RATTATA,
        .categoryName = _("Mouse"),
        .height = 3,
        .weight = 35,
        .description = COMPOUND_STRING(
            "It thrives in polluted city gutters, gaining\n"
            "immunity to all known toxins. Its dirty fur\n"
            "and sharp teeth are coated in a virulent poison\n"
            "that makes even a small scratch highly dangerous."),
        .pokemonScale = 481,
        .pokemonOffset = 21,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_RattataHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 32) : MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 16 : 8,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_RAPID_H_HOPS : ANIM_H_JUMPS,
        .backPic = gMonBackPic_RattataHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 40) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 7,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_RattataHoenn,
        .shinyPalette = gMonShinyPalette_RattataHoenn,
        .iconSprite = gMonIcon_Rattata,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(1, 3, SHADOW_SIZE_S)
        FOOTPRINT(Rattata)
        OVERWORLD(
            sPicTable_Rattata,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Rattata,
            gShinyOverworldPalette_Rattata
        )
        .levelUpLearnset = sRattataHoennLevelUpLearnset,
        .teachableLearnset = sRattataTeachableLearnset,
        .eggMoveLearnset = sRattataEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 20, SPECIES_RATICATE_HOENN}),
    },

    [SPECIES_RATICATE_HOENN] =
    {
        .baseHP        = 70,
        .baseAttack    = 86,
        .baseDefense   = 80,
        .baseSpeed     = 82,
        .baseSpAttack  = 40,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_POISON,TYPE_FIGHTING),
        .catchRate = 127,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 145 : 116,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_ANGER_POINT, ABILITY_POISON_TOUCH, ABILITY_STENCH },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Raticate"),
        .cryId = CRY_RATICATE,
        .natDexNum = NATIONAL_DEX_RATICATE,
        .categoryName = _("Mouse"),
        .height = 7,
        .weight = 185,
        .description = COMPOUND_STRING(
            "Extremely territorial and aggressive, it fights\n"
            "viciously with its front paws and massive fangs.\n"
            "It uses brawling tactics to overwhelm rivals,\n"
            "spraying toxic purple spit to blind its foes."),
        .pokemonScale = 459,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_RaticateHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 6,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_FIGURE_8 : ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL,
        .backPic = gMonBackPic_RaticateHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 40) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 4,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_RaticateHoenn,
        .shinyPalette = gMonShinyPalette_RaticateHoenn,
        .iconSprite = gMonIcon_Raticate,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(0, 8, SHADOW_SIZE_L)
        FOOTPRINT(Raticate)
        OVERWORLD(
            sPicTable_Raticate,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Raticate,
            gShinyOverworldPalette_Raticate
        )
        .levelUpLearnset = sRaticateHoennLevelUpLearnset,
        .teachableLearnset = sRaticateTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 40, SPECIES_ERATICATE}),
    },
	
	[SPECIES_ERATICATE] =
    {
        .baseHP        = 100,
        .baseAttack    = 122,
        .baseDefense   = 90,
        .baseSpeed     = 71,
        .baseSpAttack  = 50,
        .baseSpDefense = 75,
        .types = MON_TYPES(TYPE_POISON, TYPE_FIGHTING),
        .catchRate = 127,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 145 : 116,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_ANGER_POINT, ABILITY_POISON_TOUCH, ABILITY_STENCH },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Eraticate"),
        .cryId = CRY_RATICATE,
        .natDexNum = NATIONAL_DEX_RATICATE,
        .categoryName = _("Mouse"),
        .height = 7,
        .weight = 185,
        .description = COMPOUND_STRING(
            "An apex brawler of the industrial wastes.\n"
            "It stands tall on its hind legs to deliver\n"
            "crushing, venom-soaked punches. The toxic fur\n"
            "on its back can be flared to intimidate rivals."),
        .pokemonScale = 459,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Eraticate,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_FIGURE_8 : ANIM_BOUNCE_ROTATE_TO_SIDES_SMALL,
        .backPic = gMonBackPic_Eraticate,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 40) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 0,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_Eraticate,
        .shinyPalette = gMonShinyPalette_Eraticate,
        .iconSprite = gMonIcon_Raticate,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(4, 15, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Raticate)
        OVERWORLD(
            sPicTable_Raticate,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Raticate,
            gShinyOverworldPalette_Raticate
        )
        .levelUpLearnset = sEraticateLevelUpLearnset,
        .teachableLearnset = sRaticateTeachableLearnset,
        .formSpeciesIdTable = sRaticateFormSpeciesIdTable,
    },
	
	[SPECIES_SCYTHER_HOENN] =
    {
        .baseHP        = 70,
        .baseAttack    = 110,
        .baseDefense   = 60,
        .baseSpeed     = 90,
        .baseSpAttack  = 110,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_POISON, TYPE_GROUND),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 100 : 187,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_POISON_TOUCH, ABILITY_TECHNICIAN, ABILITY_SPEED_BOOST },
    #else
        .abilities = { ABILITY_SWARM, ABILITY_NONE, ABILITY_STEADFAST },
    #endif
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Scyther"),
        .cryId = CRY_SCYTHER,
        .natDexNum = NATIONAL_DEX_SCYTHER,
        .categoryName = _("Mantis"),
        .height = 15,
        .weight = 560,
        .description = COMPOUND_STRING(
            "It burrows beneath toxic swamplands. Its\n"
            "wings have adapted to mimic dead foliage,\n"
            "and its scythes secrete a corrosive acid\n"
            "capable of melting through thick mud."),
        .pokemonScale = 256,
        .pokemonOffset = 1,
        .trainerScale = 293,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_ScytherHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 64) : MON_COORDS_SIZE(56, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 0 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_VIBRATE,
        .frontAnimDelay = 10,
        .backPic = gMonBackPic_ScytherHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 3,
        .backAnimId = BACK_ANIM_TRIANGLE_DOWN,
        .palette = gMonPalette_ScytherHoenn,
        .shinyPalette = gMonShinyPalette_ScytherHoenn,
        .iconSprite = gMonIcon_Scyther,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(7, 13, SHADOW_SIZE_L)
        FOOTPRINT(Scyther)
        OVERWORLD(
            sPicTable_Scyther,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Scyther,
            gShinyOverworldPalette_Scyther
        )
        .levelUpLearnset = sScytherHoennLevelUpLearnset,
        .teachableLearnset = sScytherTeachableLearnset,
        .eggMoveLearnset = sScytherEggMoveLearnset,
		#if P_GEN_2_CROSS_EVOS || P_GEN_8_CROSS_EVOS
        .evolutions = EVOLUTION(
                            #if P_GEN_2_CROSS_EVOS
                                {EVO_TRADE, 0, SPECIES_SCIZOR_HOENN, CONDITIONS({IF_HOLD_ITEM, ITEM_METAL_COAT})},
                                {EVO_ITEM, ITEM_METAL_COAT, SPECIES_SCIZOR_HOENN}
                            #if P_GEN_8_CROSS_EVOS
                                ,
                            #endif
                            #endif
                            #if P_GEN_8_CROSS_EVOS
                                {EVO_ITEM, ITEM_BLACK_AUGURITE, SPECIES_KLEAVOR_HOENN}
                            #endif
                            ),
    #endif
    },

    [SPECIES_SCIZOR_HOENN] =
    {
        .baseHP        = 70,
        .baseAttack    = 50,
        .baseDefense   = 75,
        .baseSpeed     = 80,
        .baseSpAttack  = 125,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_POISON, TYPE_STEEL),
        .catchRate = 25,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 175 : 200,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 25,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_POISON_TOUCH, ABILITY_MEGA_LAUNCHER, ABILITY_LIGHT_METAL },
    #else
        .abilities = { ABILITY_SWARM, ABILITY_NONE, ABILITY_LIGHT_METAL },
    #endif
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Scizor"),
        .cryId = CRY_SCIZOR,
        .natDexNum = NATIONAL_DEX_SCIZOR,
        .categoryName = _("Pincer"),
        .height = 18,
        .weight = 1180,
        .description = COMPOUND_STRING(
            "Its heavy, metallic armor is stained a deep\n"
            "chemical green from its toxic habitat. When\n"
            "it clamps its pincers, noxious purple gas\n"
            "vents violently from the seams of its body."),
        .pokemonScale = 278,
        .pokemonOffset = 1,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_ScizorHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 0 : 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_VIBRATE,
        .frontAnimDelay = 19,
        .backPic = gMonBackPic_ScizorHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 4,
        .backAnimId = BACK_ANIM_JOLT_RIGHT,
        .palette = gMonPalette_ScizorHoenn,
        .shinyPalette = gMonShinyPalette_ScizorHoenn,
        .iconSprite = gMonIcon_Scizor,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(3, 14, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Scizor)
        OVERWORLD(
            sPicTable_Scizor,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Scizor,
            gShinyOverworldPalette_Scizor
        )
        .levelUpLearnset = sScizorHoennLevelUpLearnset,
        .teachableLearnset = sScizorTeachableLearnset,
    },

    [SPECIES_KLEAVOR_HOENN] =
    {
        .baseHP        = 70,
        .baseAttack    = 135,
        .baseDefense   = 100,
        .baseSpeed     = 65,
        .baseSpAttack  = 50,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_POISON, TYPE_ROCK),
        .catchRate = 15,
        .expYield = 175,
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_POISON_TOUCH, ABILITY_SHARPNESS, ABILITY_ANGER_POINT },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Kleavor"),
        .cryId = CRY_KLEAVOR,
        .natDexNum = NATIONAL_DEX_KLEAVOR,
        .categoryName = _("Axe"),
        .height = 18,
        .weight = 890,
        .description = COMPOUND_STRING(
            "Its rough, stony axes are laced with ancient,\n"
            "hardened venom. A single slash can contaminate\n"
            "the earth, leaving jagged wounds that weep\n"
            "a foul, acidic ooze that never dries."),
        .pokemonScale = 267,
        .pokemonOffset = 2,
        .trainerScale = 286,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_KleavorHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_KleavorHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 4,
        //.backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_KleavorHoenn,
        .shinyPalette = gMonShinyPalette_KleavorHoenn,
        .iconSprite = gMonIcon_Kleavor,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(4, 12, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Kleavor)
        OVERWORLD(
            sPicTable_Kleavor,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Kleavor,
            gShinyOverworldPalette_Kleavor
        )
        .levelUpLearnset = sKleavorHoennLevelUpLearnset,
        .teachableLearnset = sKleavorTeachableLearnset,
    },
	
	[SPECIES_LARVITAR_HOENN] =
    {
        .baseHP        = 90,
        .baseAttack    = 20,
        .baseDefense   = 30,
        .baseSpeed     = 40,
        .baseSpAttack  = 90,
        .baseSpDefense = 30,
        .types = MON_TYPES(TYPE_ROCK, TYPE_FIRE),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 60 : 67,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
        .abilities = { ABILITY_SOLAR_POWER, ABILITY_SOLID_ROCK, ABILITY_MAGMA_ARMOR },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Larvitar"),
        .cryId = CRY_LARVITAR,
        .natDexNum = NATIONAL_DEX_LARVITAR,
        .categoryName = _("Rock Skin"),
        .height = 6,
        .weight = 720,
        .description = COMPOUND_STRING(
            "It is born deep within active volcanoes.\n"
            "It feeds on mineral-rich ash and coal,\n"
            "which burns in its stomach to heat its\n"
            "red-hot hide to extreme temperatures."),
        .pokemonScale = 472,
        .pokemonOffset = 18,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_LarvitarHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 48) : MON_COORDS_SIZE(40, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 10,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_JUMPS_SMALL,
        .backPic = gMonBackPic_LarvitarHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(56, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_LarvitarHoenn,
        .shinyPalette = gMonShinyPalette_LarvitarHoenn,
        .iconSprite = gMonIcon_Larvitar,
        .iconPalIndex = 1,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(1, 4, SHADOW_SIZE_S)
        FOOTPRINT(Larvitar)
        OVERWORLD(
            sPicTable_Larvitar,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Larvitar,
            gShinyOverworldPalette_Larvitar
        )
        .levelUpLearnset = sLarvitarHoennLevelUpLearnset,
        .teachableLearnset = sLarvitarTeachableLearnset,
        .eggMoveLearnset = sLarvitarEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 25, SPECIES_PUPITAR_HOENN}),
    },

    [SPECIES_PUPITAR_HOENN] =
    {
        .baseHP        = 110,
        .baseAttack    = 40,
        .baseDefense   = 50,
        .baseSpeed     = 50,
        .baseSpAttack  = 110,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_ROCK, TYPE_FIRE),
        .catchRate = 45,
        .expYield = 144,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
        .abilities = { ABILITY_DROUGHT, ABILITY_SOLID_ROCK, ABILITY_MAGMA_ARMOR },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Pupitar"),
        .cryId = CRY_PUPITAR,
        .natDexNum = NATIONAL_DEX_PUPITAR,
        .categoryName = _("Hard Shell"),
        .height = 12,
        .weight = 1520,
        .description = COMPOUND_STRING(
            "Its shell is made of cooled volcanic rock.\n"
            "Highly pressurized magma builds inside it.\n"
            "By venting superheated gas from its shell,\n"
            "it can launch itself like a rocket."),
        .pokemonScale = 292,
        .pokemonOffset = 8,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_PupitarHoenn,
        .frontPicSize = MON_COORDS_SIZE(40, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 9 : 11,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_V_SHAKE : ANIM_H_SHAKE,
        .backPic = gMonBackPic_PupitarHoenn,
        .backPicSize = MON_COORDS_SIZE(48, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 3,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_PupitarHoenn,
        .shinyPalette = gMonShinyPalette_PupitarHoenn,
        .iconSprite = gMonIcon_Pupitar,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 0 : 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 5, SHADOW_SIZE_S)
        FOOTPRINT(Pupitar)
        OVERWORLD(
            sPicTable_Pupitar,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_SPOT,
            sAnimTable_Following,
            gOverworldPalette_Pupitar,
            gShinyOverworldPalette_Pupitar
        )
        .levelUpLearnset = sPupitarHoennLevelUpLearnset,
        .teachableLearnset = sPupitarTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 50, SPECIES_TYRANITAR_HOENN}),
    },

    [SPECIES_TYRANITAR_HOENN] =
    {
        .baseHP        = 150,
        .baseAttack    = 81,
        .baseDefense   = 85,
        .baseSpeed     = 60,
        .baseSpAttack  = 134,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_ROCK, TYPE_FIRE),
        .catchRate = 45,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 300,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 270,
    #else
        .expYield = 218,
    #endif
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 40,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_MONSTER),
        .abilities = { ABILITY_DROUGHT, ABILITY_SOLID_ROCK, ABILITY_MAGMA_ARMOR },
        .bodyColor = BODY_COLOR_GREEN,
        .speciesName = _("Tyranitar"),
        .cryId = CRY_TYRANITAR,
        .natDexNum = NATIONAL_DEX_TYRANITAR,
        .categoryName = _("Armor"),
        .height = 20,
        .weight = 2020,
        .description = COMPOUND_STRING(
            "Its armored body is made of hard obsidian,\n"
            "veined with roaring, molten magma. It can\n"
            "melt down entire mountains with its fiery\n"
            "breath to reshape its territory."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 345,
        .trainerOffset = 7,
        .frontPic = gMonFrontPic_TyranitarHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = P_GBA_STYLE_SPECIES_GFX ? ANIM_H_SHAKE : ANIM_V_SHAKE,
        .frontAnimDelay = 10,
        .backPic = gMonBackPic_TyranitarHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 0 : 1,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_TyranitarHoenn,
        .shinyPalette = gMonShinyPalette_TyranitarHoenn,
        .iconSprite = gMonIcon_Tyranitar,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 1 : 4,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-4, 14, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Tyranitar)
        OVERWORLD(
            sPicTable_Tyranitar,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Tyranitar,
            gShinyOverworldPalette_Tyranitar
        )
        .levelUpLearnset = sTyranitarHoennLevelUpLearnset,
        .teachableLearnset = sTyranitarTeachableLearnset,
    },
	
	[SPECIES_SWINUB_HOENN] =
    {
        .baseHP        = 45,
        .baseAttack    = 55,
        .baseDefense   = 45,
        .baseSpeed     = 35,
        .baseSpAttack  = 25,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GROUND, TYPE_GRASS),
        .catchRate = 225,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 50 : 78,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_HARVEST, ABILITY_SAP_SIPPER, ABILITY_OWN_TEMPO },
    #else
        .abilities = { ABILITY_OBLIVIOUS, ABILITY_NONE, ABILITY_THICK_FAT },
    #endif
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Swinub"),
        .cryId = CRY_SWINUB,
        .natDexNum = NATIONAL_DEX_SWINUB,
        .categoryName = _("Pig"),
        .height = 4,
        .weight = 65,
        .description = COMPOUND_STRING(
            "It mimics a small bush to hide from\n"
            "predators. It digs through soft soil\n"
            "with its nose, hunting for delicious\n"
            "roots and buried berries to eat."),
        .pokemonScale = 324,
        .pokemonOffset = 20,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SwinubHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(32, 24) : MON_COORDS_SIZE(40, 32),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 20 : 15,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_SwinubHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 24) : MON_COORDS_SIZE(56, 40),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 21 : 15,
        .backAnimId = BACK_ANIM_V_SHAKE_H_SLIDE,
        .palette = gMonPalette_SwinubHoenn,
        .shinyPalette = gMonShinyPalette_SwinubHoenn,
        .iconSprite = gMonIcon_Swinub,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NORMAL,
        SHADOW(0, -2, SHADOW_SIZE_M)
        FOOTPRINT(Swinub)
        OVERWORLD(
            sPicTable_Swinub,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Swinub,
            gShinyOverworldPalette_Swinub
        )
        .levelUpLearnset = sSwinubHoennLevelUpLearnset,
        .teachableLearnset = sSwinubTeachableLearnset,
        .eggMoveLearnset = sSwinubEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 23, SPECIES_PILOSWINE_HOENN}),
    },

    [SPECIES_PILOSWINE_HOENN] =
    {
        .baseHP        = 70,
        .baseAttack    = 102,
        .baseDefense   = 84,
        .baseSpeed     = 74,
        .baseSpAttack  = 55,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_GROUND, TYPE_GRASS),
        .catchRate = 75,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 158 : 160,
        .evYield_HP = 1,
        .evYield_Attack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
    #if P_UPDATED_ABILITIES >= GEN_4
        .abilities = { ABILITY_HARVEST, ABILITY_SAP_SIPPER, ABILITY_OWN_TEMPO },
    #else
        .abilities = { ABILITY_OBLIVIOUS, ABILITY_NONE, ABILITY_THICK_FAT },
    #endif
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Piloswine"),
        .cryId = CRY_PILOSWINE,
        .natDexNum = NATIONAL_DEX_PILOSWINE,
        .categoryName = _("Swine"),
        .height = 11,
        .weight = 558,
        .description = COMPOUND_STRING(
            "Its body is covered in thick leaves.\n"
            "Since its eyes are totally covered,\n"
            "it relies on its yellow tusks to\n"
            "plow through dense undergrowth."),
        .pokemonScale = 306,
        .pokemonOffset = 10,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_PiloswineHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(48, 48) : MON_COORDS_SIZE(48, 56),
        .frontPicYOffset = 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE,
        .backPic = gMonBackPic_PiloswineHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 40) : MON_COORDS_SIZE(64, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 13 : 8,
        .backAnimId = BACK_ANIM_H_SHAKE,
        .palette = gMonPalette_PiloswineHoenn,
        .shinyPalette = gMonShinyPalette_PiloswineHoenn,
        .iconSprite = gMonIcon_Piloswine,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(2, 10, SHADOW_SIZE_L)
        FOOTPRINT(Piloswine)
        OVERWORLD(
            sPicTable_Piloswine,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Piloswine,
            gShinyOverworldPalette_Piloswine
        )
        .levelUpLearnset = sPiloswineHoennLevelUpLearnset,
        .teachableLearnset = sPiloswineTeachableLearnset,
    #if P_GEN_4_CROSS_EVOS
        .evolutions = EVOLUTION({EVO_LEVEL, 44, SPECIES_MAMOSWINE_HOENN}),
    #endif
    },

    [SPECIES_MAMOSWINE_HOENN] =
    {
        .baseHP        = 110,
        .baseAttack    = 120,
        .baseDefense   = 80,
        .baseSpeed     = 70,
        .baseSpAttack  = 70,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GROUND, TYPE_GRASS),
        .catchRate = 50,
    #if P_UPDATED_EXP_YIELDS >= GEN_8
        .expYield = 265,
    #elif P_UPDATED_EXP_YIELDS >= GEN_5
        .expYield = 239,
    #else
        .expYield = 207,
    #endif
        .evYield_Attack = 3,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_THICK_FAT, ABILITY_SAP_SIPPER, ABILITY_GRASSY_SURGE },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Mamoswine"),
        .cryId = CRY_MAMOSWINE,
        .natDexNum = NATIONAL_DEX_MAMOSWINE,
        .categoryName = _("Twin Tusk"),
        .height = 25,
        .weight = 2910,
        .description = COMPOUND_STRING(
            "A primeval titan of ancient forests.\n"
            "Sweet, colorful fruits grow along its\n"
            "leafy back. It aggressively defends\n"
            "them with its massive yellow tusks."),
        .pokemonScale = 257,
        .pokemonOffset = 6,
        .trainerScale = 423,
        .trainerOffset = 8,
        .frontPic = gMonFrontPic_MamoswineHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_BACK_AND_LUNGE,
        .backPic = gMonBackPic_MamoswineHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_MamoswineHoenn,
        .shinyPalette = gMonShinyPalette_MamoswineHoenn,
        .iconSprite = gMonIcon_Mamoswine,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(7, 10, SHADOW_SIZE_XL_BATTLE_ONLY)
        FOOTPRINT(Mamoswine)
        OVERWORLD(
            sPicTable_Mamoswine,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Mamoswine,
            gShinyOverworldPalette_Mamoswine
        )
        .levelUpLearnset = sMamoswineHoennLevelUpLearnset,
        .teachableLearnset = sMamoswineTeachableLearnset,
    },
	
	[SPECIES_HOUNDOUR_HOENN] =
    {
        .baseHP        = 45,
        .baseAttack    = 50,
        .baseDefense   = 35,
        .baseSpeed     = 75,
        .baseSpAttack  = 95,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 120,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 66 : 114,
        .evYield_SpAttack = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_FLASH_FIRE, ABILITY_FLAME_BODY },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Houndour"),
        .cryId = CRY_HOUNDOUR,
        .natDexNum = NATIONAL_DEX_HOUNDOUR,
        .categoryName = _("Dark"),
        .height = 6,
        .weight = 108,
        .description = COMPOUND_STRING(
            "Its body is made of cold shadows.\n"
            "When it howls in the dead of night,\n"
            "the spectral flames on its back flare\n"
            "freezing the hearts of nearby prey."),
        .pokemonScale = 393,
        .pokemonOffset = 16,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_HoundourHoenn,
        .frontPicSize = MON_COORDS_SIZE(40, 48),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 11 : 13,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_STRETCH,
        .backPic = gMonBackPic_HoundourHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(40, 40) : MON_COORDS_SIZE(40, 48),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 12 : 5,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_HoundourHoenn,
        .shinyPalette = gMonShinyPalette_HoundourHoenn,
        .iconSprite = gMonIcon_Houndour,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_FAST,
        SHADOW(2, 0, SHADOW_SIZE_M)
        FOOTPRINT(Houndour)
        OVERWORLD(
            sPicTable_Houndour,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Houndour,
            gShinyOverworldPalette_Houndour
        )
        .levelUpLearnset = sHoundourHoennLevelUpLearnset,
        .teachableLearnset = sHoundourTeachableLearnset,
        .eggMoveLearnset = sHoundourEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 24, SPECIES_HOUNDOOM_HOENN}),
    },

    [SPECIES_HOUNDOOM_HOENN] =
    {
        .baseHP        = 75,
        .baseAttack    = 90,
        .baseDefense   = 50,
        .baseSpeed     = 105,
        .baseSpAttack  = 130,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_GHOST),
        .catchRate = 45,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 175 : 204,
        .evYield_SpAttack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = 35,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_FIELD),
        .abilities = { ABILITY_INTIMIDATE, ABILITY_FLASH_FIRE, ABILITY_FLAME_BODY },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Houndoom"),
        .cryId = CRY_HOUNDOOM,
        .natDexNum = NATIONAL_DEX_HOUNDOOM,
        .categoryName = _("Dark"),
        .height = 14,
        .weight = 350,
        .description = COMPOUND_STRING(
            "An eerie Pokémon that wanders ruins.\n"
            "The ghostly rib-like wisps on its\n"
            "back burn with a silent, cold fire\n"
            "that inflicts pain directly to the soul."),
        .pokemonScale = 256,
        .pokemonOffset = 4,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_HoundoomHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 56) : MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 2,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SHAKE,
        .backPic = gMonBackPic_HoundoomHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 7 : 6,
        .backAnimId = BACK_ANIM_V_SHAKE,
        .palette = gMonPalette_HoundoomHoenn,
        .shinyPalette = gMonShinyPalette_HoundoomHoenn,
        .iconSprite = gMonIcon_Houndoom,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-5, 11, SHADOW_SIZE_L)
        FOOTPRINT(Houndoom)
        OVERWORLD(
            sPicTable_Houndoom,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Houndoom,
            gShinyOverworldPalette_Houndoom
        )
        .levelUpLearnset = sHoundoomHoennLevelUpLearnset,
        .teachableLearnset = sHoundoomTeachableLearnset,
    },
	
	[SPECIES_GLIGAR_HOENN] =
    {
        .baseHP        = 55,
        .baseAttack    = 85,
        .baseDefense   = 85,
        .baseSpeed     = 95,
        .baseSpAttack  = 60,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_POISON, TYPE_FIRE),
        .catchRate = 60,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 86 : 108,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_POISON_POINT, ABILITY_FLAME_BODY, ABILITY_SHELL_ARMOR },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("Gligar"),
        .cryId = CRY_GLIGAR,
        .natDexNum = NATIONAL_DEX_GLIGAR,
        .categoryName = _("Fly Scorpion"),
        .height = 11,
        .weight = 648,
        .description = COMPOUND_STRING(
            "It glides silently on volcanic updrafts.\n"
            "It hangs from cavern ceilings, waiting to\n"
            "drop onto prey and inject a boiling, toxic\n"
            "venom from the stinger on its tail."),
        .pokemonScale = 350,
        .pokemonOffset = -1,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_GligarHoenn,
        .frontPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(56, 64) : MON_COORDS_SIZE(56, 56),
        .frontPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 3 : 4,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_SHRINK_GROW,
        .enemyMonElevation = P_GBA_STYLE_SPECIES_GFX ? 6 : 8,
        .backPic = gMonBackPic_GligarHoenn,
        .backPicSize = P_GBA_STYLE_SPECIES_GFX ? MON_COORDS_SIZE(64, 56) : MON_COORDS_SIZE(64, 64),
        .backPicYOffset = P_GBA_STYLE_SPECIES_GFX ? 5 : 2,
        .backAnimId = BACK_ANIM_SHRINK_GROW,
        .palette = gMonPalette_GligarHoenn,
        .shinyPalette = gMonShinyPalette_GligarHoenn,
        .iconSprite = gMonIcon_Gligar,
        .iconPalIndex = P_GBA_STYLE_SPECIES_ICONS ? 2 : 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(0, 15, SHADOW_SIZE_S)
        FOOTPRINT(Gligar)
        OVERWORLD(
            sPicTable_Gligar,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_NONE,
            sAnimTable_Following,
            gOverworldPalette_Gligar,
            gShinyOverworldPalette_Gligar
        )
        .levelUpLearnset = sGligarHoennLevelUpLearnset,
        .teachableLearnset = sGligarTeachableLearnset,
        .eggMoveLearnset = sGligarEggMoveLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 30, SPECIES_GLISCOR_HOENN}),
    },

    [SPECIES_GLISCOR_HOENN] =
    {
        .baseHP        = 65,
        .baseAttack    = 105,
        .baseDefense   = 105,
        .baseSpeed     = 105,
        .baseSpAttack  = 70,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_POISON, TYPE_FIRE),
        .catchRate = 30,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 179 : 192,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_POISON_POINT, ABILITY_FLAME_BODY, ABILITY_SHELL_ARMOR },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("Gliscor"),
        .cryId = CRY_GLISCOR,
        .natDexNum = NATIONAL_DEX_GLISCOR,
        .categoryName = _("Fang Scorp"),
        .height = 20,
        .weight = 425,
        .description = COMPOUND_STRING(
            "Its body heat is so intense that toxic\n"
            "sludge turns to searing magma inside its\n"
            "pincers. It deliberately drips this molten\n"
            "fluid to melt its opponent's defenses."),
        .pokemonScale = 261,
        .pokemonOffset = 1,
        .trainerScale = 334,
        .trainerOffset = 4,
        .frontPic = gMonFrontPic_GliscorHoenn,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_SWING_CONVEX,
        .enemyMonElevation = 9,
        .backPic = gMonBackPic_GliscorHoenn,
        .backPicSize = MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 1,
        .backAnimId = BACK_ANIM_V_STRETCH,
        .palette = gMonPalette_GliscorHoenn,
        .shinyPalette = gMonShinyPalette_GliscorHoenn,
        .iconSprite = gMonIcon_Gliscor,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 13, SHADOW_SIZE_M)
        FOOTPRINT(Gliscor)
        OVERWORLD(
            sPicTable_Gliscor,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Gliscor,
            gShinyOverworldPalette_Gliscor
        )
        .levelUpLearnset = sGliscorHoennLevelUpLearnset,
        .teachableLearnset = sGliscorTeachableLearnset,
		.evolutions = EVOLUTION({EVO_LEVEL, 50, SPECIES_MAGMENOUS}),
    },
	
	[SPECIES_MAGMENOUS] =
    {
        .baseHP        = 80,
        .baseAttack    = 120,
        .baseDefense   = 125,
        .baseSpeed     = 125,
        .baseSpAttack  = 70,
        .baseSpDefense = 60,
        .types = MON_TYPES(TYPE_POISON, TYPE_FIRE),
        .catchRate = 30,
        .expYield = (P_UPDATED_EXP_YIELDS >= GEN_5) ? 179 : 192,
        .evYield_Defense = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_BUG),
        .abilities = { ABILITY_POISON_POINT, ABILITY_FLAME_BODY, ABILITY_SHELL_ARMOR },
        .bodyColor = BODY_COLOR_PURPLE,
        .speciesName = _("Magmenous"),
        .cryId = CRY_GLISCOR,
        .natDexNum = NATIONAL_DEX_GLISCOR,
        .categoryName = _("Fang Scorp"),
        .height = 20,
        .weight = 425,
        .description = COMPOUND_STRING(
            "Born from extreme volcanic pressure, its\n"
            "stony shell is constantly melting. It flies\n"
            "through ash clouds, raining down globs of\n"
            "highly poisonous, white-hot molten rock."),
        .pokemonScale = 261,
        .pokemonOffset = 1,
        .trainerScale = 334,
        .trainerOffset = 4,
        .frontPic = gMonFrontPic_Magmenous,
        .frontPicSize = MON_COORDS_SIZE(64, 56),
        .frontPicYOffset = 7,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .enemyMonElevation = 9,
        .backPic = gMonBackPic_Magmenous,
        .backPicSize = MON_COORDS_SIZE(64, 48),
        .backPicYOffset = 1,
        .backAnimId = BACK_ANIM_V_STRETCH,
        .palette = gMonPalette_Magmenous,
        .shinyPalette = gMonShinyPalette_Magmenous,
        .iconSprite = gMonIcon_Gliscor,
        .iconPalIndex = 2,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        SHADOW(-1, 13, SHADOW_SIZE_L)
        FOOTPRINT(Gliscor)
        OVERWORLD(
            sPicTable_Gliscor,
            SIZE_32x32,
            SHADOW_SIZE_M,
            TRACKS_FOOT,
            sAnimTable_Following,
            gOverworldPalette_Gliscor,
            gShinyOverworldPalette_Gliscor
        )
        .levelUpLearnset = sMagmenousLevelUpLearnset,
        .teachableLearnset = sGliscorTeachableLearnset,
    },

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_CircledQuestionMark,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicFemale = gMonBackPic_CircledQuestionMarkF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSpriteFemale = gMonIcon_QuestionMarkF,
        .iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    */
};

const struct EggData gEggDatas[EGG_ID_COUNT] =
{
#include "egg_data.h"
};
