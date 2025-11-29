#include <string.h>
#include "functions.h"


status_code convert_to_p(const int p, const int *number, char *answer) {
    if (!number || !answer) return INPUT_ERROR;

    int r = 0;

    if (p == 2) {
        status_code status = convert_to_2(number, answer);
        return status;
    }

    else if (p == 4) r = 2;
    else if (p == 8) r = 3;
    else if (p == 16) r = 4;
    else if (p == 32) r = 5;
    else return INPUT_ERROR;

    char bin[33];
    int_to_binary(*number, bin);

    int i = 31;
    int idx = 0;
    int bit_cnt = 0;
    int out = 0;

    while (i >= 0) {
        int bit = bin[31 - i] & 1;

        out |= (bit << (bit_sub(r, bit_add(bit_cnt, 1))));
        bit_cnt = bit_add(bit_cnt, 1);

        if (bit_cnt == r) {
            char c;

            if (out < 10)
                c = bit_add('0', out);
            else
                c = bit_add('A', bit_sub(out, 10));

            answer[idx] = c;
            idx = bit_add(idx, 1);

            out = 0;
            bit_cnt = 0;
        }

        i = bit_sub(i, 1);
    }

    answer[idx] = '\0';
    remove_leading_zeros(answer);

    return OK;
}

status_code convert_to_2(const int *number, char *answer) {
    if (!number || !answer) return INPUT_ERROR;

    int i = 31;
    int pos = 0;

    while (i >= 0) {
        answer[pos] = (( (*number >> i) & 1 ) | '0');
        pos = bit_add(pos, 1);
        i = bit_sub(i, 1);
    }

    answer[pos] = '\0';

    remove_leading_zeros(answer);
    return OK;
}

int bit_add(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

int bit_sub(int a, int b) {
    while (b != 0) {
        int borrow = (~a & b) << 1;
        a = a ^ b;
        b = borrow;
    }
    return a;
}

static void int_to_binary(int num, char *bin) {
    int i = 31;
    int pos = 0;

    while (i >= 0) {
        bin[pos] = ((num >> i) & 1) | '0';
        pos = bit_add(pos, 1);
        i = bit_sub(i, 1);
    }
    bin[32] = '\0';
}

status_code remove_leading_zeros(char *str) {
    int len = strlen(str);
    int i = 0;

    while (i < bit_sub(len, 1) && str[i] == '0') {
        i = bit_add(i, 1);
    }

    if (i > 0) {
        memmove(str, str + i, bit_add(len, 1) - i);
    }
    return OK;
}