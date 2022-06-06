//
// Created by pat on 06.06.2022.
//

#ifndef Z5_NEGATYW_HEADER_H
#define Z5_NEGATYW_HEADER_H

union fourBytes {
    unsigned char b[4];
    unsigned long l;
};

unsigned char negativeValue(unsigned char v);

#endif //Z5_NEGATYW_HEADER_H
