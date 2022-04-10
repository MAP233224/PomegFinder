#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define STRING_LENGTH_MAX 16
#define EVS_MIN 0
#define EVS_MAX 245
#define LEVEL_MIN 1
#define LEVEL_MAX 100
#define BASE_STAT_MIN 5
#define BASE_STAT_MAX 250

static void ScanValue(u8* message, u32* value, u8* format, u64 min, u64 max) {
	/* General purpose safe scan. Instruction message, value to change, string format and max value */
	do {
		printf("%s", message);
		u8 userInput[STRING_LENGTH_MAX];
		fgets(userInput, STRING_LENGTH_MAX, stdin);
		if (strlen(userInput) == 0 || strlen(userInput) >= STRING_LENGTH_MAX)
		{
			continue;
		}
		if (sscanf(userInput, format, value) != 1)
		{
			*value = max + 1;
			continue;
		}
	} while (*value > max || *value < min);
}

u32 IvToStat_HP(u32 base, u32 iv, u32 evs, u32 lv) {
	/* Return the value of the HP stat based on the IV, EVs, Base Stat and Level */
	return (2 * base + iv + evs / 4) * lv / 100 + lv + 10;
}

int main() {

	while (1)

	{
		u32 results = 0;

		u32 level_min = 0;
		u32 level_max = 100;
		u32 evs = 0;
		u32 base_hp = 80;
		ScanValue("Level min: ", &level_min, "%u", LEVEL_MIN, LEVEL_MAX);
		ScanValue("Level max: ", &level_max, "%u", LEVEL_MIN, LEVEL_MAX);
		ScanValue("EVs (-10): ", &evs, "%u", EVS_MIN, EVS_MAX);
		ScanValue("Base HP: ", &base_hp, "%u", BASE_STAT_MIN, BASE_STAT_MAX);

		if (level_min > level_max) //swap them
		{
			u32 tmp = level_max;
			level_max = level_min;
			level_min = tmp;
		}

		for (u32 level = level_min; level <= level_max; level++) {
			for (u32 iv = 0; iv <= 31; iv++) {
				if ((IvToStat_HP(base_hp, iv, evs+10, level) - IvToStat_HP(base_hp, iv, evs, level)) == 2) {
					printf("\nLv. %-6u IV = %u", level, iv);
					results++;
				}
			}
		}

		if (results) printf("\n");
		printf("\nFound %u results.\n", results);
		printf("\n--------------------------------\n\n");
	}

	return 0;
}
