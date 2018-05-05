inline int bit_count(unsigned long long num) {
    num = (num & 0x5555555555555555)
        + ((num >> 1) & 0x5555555555555555);
    num = (num & 0x3333333333333333)
        + ((num >> 2) & 0x3333333333333333);
    num = (num & 0x0f0f0f0f0f0f0f0f)
        + ((num >> 4) & 0x0f0f0f0f0f0f0f0f);
    num = (num & 0x00ff00ff00ff00ff)
        + ((num >> 8) & 0x00ff00ff00ff00ff);
    num = (num & 0x0000ffff0000ffff)
        + ((num >> 16) & 0x0000ffff0000ffff);
    num = (num & 0x00000000ffffffff)
        + ((num >> 32) & 0x00000000ffffffff);
    return num;
}
