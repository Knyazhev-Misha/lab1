#include <gtest/gtest.h>
#include "TritSet.h"

TEST(Test, TritSet_get_capacity){
    TritSet tritset1(1000);
    size_t qt = tritset1.get_capacity();
    ASSERT_EQ(qt, 1000);

    TritSet tritset2;
    qt = tritset2.get_capacity();
    ASSERT_EQ(qt, 0);
}

TEST(Test, TritSet_shrink){
    TritSet tritset1(1000);
    size_t qt = tritset1.get_capacity();
    ASSERT_EQ(qt, 1000);
    tritset1.shrink();
    qt = tritset1.get_capacity();
    ASSERT_EQ(qt,0);

    TritSet tritset2(1000);
    qt = tritset2.get_capacity();
    ASSERT_EQ(qt, 1000);
    tritset2[500] = FALSE;
    tritset2.shrink();
    qt = tritset2.get_capacity();
    ASSERT_EQ(qt, 501);
}

TEST(Test, TritSet_get_ln_vector){
    TritSet tritset(1000);
    size_t qt;
    qt = tritset.get_ln_vecor();
    ASSERT_EQ(qt, 63);
}

TEST(Test, TritSet_trim){
    TritSet tritset(1000);
    size_t qt;
    tritset.trim(145);
    qt = tritset.get_capacity();
    ASSERT_EQ(qt, 146);
    qt = tritset.get_ln_vecor();
    ASSERT_EQ(qt, 9);
}

TEST(TEST, TritSet_cardinality){
    TritSet tritset(1000);
    size_t qt;
    for(int i = 101; i < 201; i += 1)
        tritset[i] = TRUE;

    tritset[0] = FALSE;
    tritset[786] = FALSE;

    qt = tritset.cardinality(TRUE);
    ASSERT_EQ(qt, 100);

    qt = tritset.cardinality(FALSE);
    ASSERT_EQ(qt, 2);

    qt = tritset.cardinality(UNKNOWN);
    ASSERT_EQ(qt, 898);
}

TEST(TEST, TritSet_lenght){
    TritSet tritset(1000);
    size_t qt = tritset.lenght();
    ASSERT_EQ(qt, 0);

    tritset[500] = TRUE;
    qt = tritset.lenght();
    ASSERT_EQ(qt, 501);
}

TEST(TEST, TritSet_cardinality_map) {
    TritSet  tritset(100);
    tritset[20] = TRUE;
    tritset[80] = TRUE;
    tritset[99] = TRUE;
    tritset[0] = FALSE;
    std::unordered_map< Trit, int, std::hash<int> > map;
    map = tritset.cardinality();
    ASSERT_EQ(3,map[TRUE]);
    ASSERT_EQ(1,map[FALSE]);
    ASSERT_EQ(96,map[UNKNOWN]);
}

TEST(TEST, TritSet_operator_index){
    TritSet  tritset1(1000);
    tritset1[20] = TRUE;
    tritset1[80] = FALSE;
    tritset1[99] = TRUE;
    tritset1[99] = UNKNOWN;
    ASSERT_EQ(tritset1[20], TRUE);
    ASSERT_EQ(tritset1[80], FALSE);
    ASSERT_EQ(tritset1[99], UNKNOWN);

    tritset1[99] = tritset1[80];
    ASSERT_EQ(tritset1[99], FALSE);
    tritset1[99] = tritset1[20];
    ASSERT_EQ(tritset1[99], TRUE);

    const TritSet tritset2 = tritset1;
    Trit set = tritset2[20];
    ASSERT_EQ(set, TRUE);
}

TEST(TEST, TritSet_and){
    TritSet tritset1(500), tritset2(1000), check(1000), result;

    for(int i = 101; i < 301; i += 1) {
        tritset1[i] = TRUE;

        if(i > 150 && i < 200) {
            tritset2[i] = FALSE;
            check[i] = FALSE;
        }

        if(i > 199){
            tritset2[i] = TRUE;
            check[i] = TRUE;
        }
    }

    result = tritset1 & tritset2;

    for(int i = 0; i < 1000; i += 1)
        ASSERT_EQ(check[i], result[i]);

}


TEST(TEST, TritSet_or){
    TritSet tritset1(500), tritset2(1000), check(1000), result;

    for(int i = 101; i < 301; i += 1) {
        tritset1[i] = FALSE;

        if(i > 150 && i < 200) {
            tritset2[i] = FALSE;
            check[i] = FALSE;
        }

        if(i > 199){
            tritset2[i] = TRUE;
            check[i] = TRUE;
        }
    }

    result = tritset1 | tritset2;

    for(int i = 0; i < 1000; i += 1)
        ASSERT_EQ(check[i], result[i]);

}

TEST(TEST, TritSet_not){
    TritSet tritset1(500), check(500), result;

    for(int i = 101; i < 301; i += 1) {
        if( i < 200) {
            check[i] = FALSE;
            tritset1[i] = TRUE;
        }

        if(i > 199) {
            check[i] = TRUE;
            tritset1[i] = FALSE;
        }
    }

    result = ~tritset1;
    tritset1 = ~tritset1;
    for(int i = 0; i < 500; i += 1) {
        ASSERT_EQ(check[i], result[i]);
        ASSERT_EQ(check[i], tritset1[i]);
    }
}

TEST(TEST, TritSet_iterator_notequal) {
    TritSet tritset1(1000);
    TritSet tritset2(1000);

    auto it1 = tritset1.begin();
    auto it2 = tritset2.begin();

    ASSERT_NE(it1, it2);

    it2 = tritset1.begin();
    ASSERT_EQ(it1, it2);

    it2 = tritset1.end();

    ASSERT_NE(it1, it2);
}

TEST(TEST, TritSet_iterator){
    TritSet tritset(1000);

    for(int i = 0; i < 1000; i += 1) {
        ASSERT_EQ(tritset[i], UNKNOWN);
    }

    for(auto it : tritset){
       it = TRUE;
    }

    for(int i = 0; i < 1000; i += 1){
        ASSERT_EQ(tritset[i], TRUE);
    }

    for(auto it : tritset){
        it = FALSE;
    }

    for(int i = 0; i < 1000; i += 1){
        ASSERT_EQ(tritset[i], FALSE);
    }
}

TEST(TEST, TritSet_iterator_other_capacity_memory){
    TritSet tritset(1000);
    size_t qt = tritset.get_capacity();
    ASSERT_EQ(qt, 1000);

    auto it = tritset.end();
    it++;
    it++;
    it = TRUE;
    qt = tritset.get_capacity();
    ASSERT_EQ(qt, 1003);
    ASSERT_EQ(tritset[1002], TRUE);
}

TEST(TEST, TritSet_iterator_other_capacity_withoutmemory){
    TritSet tritset(1000);
    size_t qt = tritset.get_capacity();
    ASSERT_EQ(qt, 1000);

    auto it = tritset.end();
    it++;
    it++;
    it = UNKNOWN;
    qt = tritset.get_capacity();
    ASSERT_EQ(qt, 1000);
    ASSERT_EQ(tritset[1002], UNKNOWN);
}