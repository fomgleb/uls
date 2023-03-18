#include "../inc/time.h"

char *mx_get_month_str_by_id(char month_id) {
    switch (month_id)
    {
    case 0:
        return mx_strdup(JANUARY_ABBREVIATION);
        break;
    case 1:
        return mx_strdup(FEBRUARY_ABBREVIATION);
        break;
    case 2:
        return mx_strdup(MARCH_ABBREVIATION);
        break;
    case 3:
        return mx_strdup(APRIL_ABBREVIATION);
        break;
    case 4:
        return mx_strdup(MAY_ABBREVIATION);
        break;
    case 5:
        return mx_strdup(JUNE_ABBREVIATION);
        break;
    case 6:
        return mx_strdup(JULY_ABBREVIATION);
        break;
    case 7:
        return mx_strdup(AUGUST_ABBREVIATION);
        break;
    case 8:
        return mx_strdup(SEPTEMBER_ABBREVIATION);
        break;
    case 9:
        return mx_strdup(OCTOBER_ABBREVIATION);
        break;
    case 10:
        return mx_strdup(NOVEMBER_ABBREVIATION);
        break;
    case 11:
        return mx_strdup(DECEMBER_ABBREVIATION);
        break;
    default:
        mx_printerr("Operator error: switch: month id can't be lower than 0 and greater than 11");
        exit(EXIT_FAILURE);
    }
}

