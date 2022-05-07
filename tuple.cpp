template<typename T1, typename T2> struct t2
    {
        private:

        T1 E1;
        T2 E2;

        public:

        t2() = default;

        t2(const T1& _e1, const T2& _e2) : E1(_e1), E2(_e2) {}

        t2(const t2&) = default;

        t2& operator=(const t2&) = default;

        bool operator==(const t2& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2();
        }

        bool operator!=(const t2& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }
    };

    template<typename T1, typename T2, typename T3> struct t3
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;

        public:

        t3() = default;

        t3(const T1& _e1, const T2& _e2, const T3& _e3) : E1(_e1), E2(_e2), E3(_e3) {}

        t3(const t3&) = default;

        t3& operator=(const t3&) = default;

        bool operator==(const t3& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3();
        }

        bool operator!=(const t3& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }
    };

    template<typename T1, typename T2, typename T3, typename T4> struct t4
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;
        T4 E4;

        public:

        t4() = default;

        t4(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4) : E1(_e1), E2(_e2), E3(_e3), E4(_e4) {}

        t4(const t4&) = default;

        t4& operator=(const t4&) = default;

        bool operator==(const t4& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4();
        }

        bool operator!=(const t4& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }

        const T4& e4() const
        {
            return E4;
        }
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5> struct t5
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;
        T4 E4;
        T5 E5;

        public:

        t5() = default;

        t5(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5) : E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5) {}

        t5(const t5&) = default;

        t5& operator=(const t5&) = default;

        bool operator==(const t5& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5();
        }

        bool operator!=(const t5& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }

        const T4& e4() const
        {
            return E4;
        }

        const T5& e5() const
        {
            return E5;
        }
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct t6
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;
        T4 E4;
        T5 E5;
        T6 E6;

        public:

        t6() = default;

        t6(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6) : E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6) {}

        t6(const t6&) = default;

        t6& operator=(const t6&) = default;

        bool operator==(const t6& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() &&
            E5 == _tuple.e5() && E6 == _tuple.e6();
        }

        bool operator!=(const t6& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() ||
            E5 != _tuple.e5() || E6 != _tuple.e6();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }

        const T4& e4() const
        {
            return E4;
        }

        const T5& e5() const
        {
            return E5;
        }

        const T6& e6() const
        {
            return E6;
        }
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct t7
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;
        T4 E4;
        T5 E5;
        T6 E6;
        T7 E7;

        public:

        t7() = default;

        t7(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7) : E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7) {}

        t7(const t7&) = default;

        t7& operator=(const t7&) = default;

        bool operator==(const t7& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() &&
            E5 == _tuple.e5() && E6 == _tuple.e6() && E7 == _tuple.e7();
        }

        bool operator!=(const t7& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() ||
            E5 != _tuple.e5() || E6 != _tuple.e6() || E7 != _tuple.e7();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }

        const T4& e4() const
        {
            return E4;
        }

        const T5& e5() const
        {
            return E5;
        }

        const T6& e6() const
        {
            return E6;
        }

        const T7& e7() const
        {
            return E7;
        }
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct t8
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;
        T4 E4;
        T5 E5;
        T6 E6;
        T7 E7;
        T8 E8;

        public:

        t8() = default;

        t8(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8) {}

        t8(const t8&) = default;

        t8& operator=(const t8&) = default;

        bool operator==(const t8& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() &&
            E5 == _tuple.e5() && E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8();
        }

        bool operator!=(const t8& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() ||
            E5 != _tuple.e5() || E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }

        const T4& e4() const
        {
            return E4;
        }

        const T5& e5() const
        {
            return E5;
        }

        const T6& e6() const
        {
            return E6;
        }

        const T7& e7() const
        {
            return E7;
        }

        const T8& e8() const
        {
            return E8;
        }
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct t9
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;
        T4 E4;
        T5 E5;
        T6 E6;
        T7 E7;
        T8 E8;
        T9 E9;

        public:

        t9() = default;

        t9(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9) {}

        t9(const t9&) = default;

        t9& operator=(const t9&) = default;

        bool operator==(const t9& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() &&
            E5 == _tuple.e5() && E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9();
        }

        bool operator!=(const t9& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() ||
            E5 != _tuple.e5() || E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }

        const T4& e4() const
        {
            return E4;
        }

        const T5& e5() const
        {
            return E5;
        }

        const T6& e6() const
        {
            return E6;
        }

        const T7& e7() const
        {
            return E7;
        }

        const T8& e8() const
        {
            return E8;
        }

        const T9& e9() const
        {
            return E9;
        }
    };

    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10> struct t10
    {
        private:

        T1 E1;
        T2 E2;
        T3 E3;
        T4 E4;
        T5 E5;
        T6 E6;
        T7 E7;
        T8 E8;
        T9 E9;
        T10 E10;

        public:

        t10() = default;

        t10(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10) {}

        t10(const t10&) = default;

        t10& operator=(const t10&) = default;

        bool operator==(const t10& _tuple) const
        {
            return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
                E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10();
        }

        bool operator!=(const t10& _tuple) const
        {
            return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
                E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10();
        }

        const T1& e1() const
        {
            return E1;
        }

        const T2& e2() const
        {
            return E2;
        }

        const T3& e3() const
        {
            return E3;
        }

        const T4& e4() const
        {
            return E4;
        }

        const T5& e5() const
        {
            return E5;
        }

        const T6& e6() const
        {
            return E6;
        }

        const T7& e7() const
        {
            return E7;
        }

        const T8& e8() const
        {
            return E8;
        }

        const T9& e9() const
        {
            return E9;
        }

        const T10& e10() const
        {
            return E10;
        }
    };

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11> struct t11
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;

public:

    t11() = default;

    t11(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11) {}

    t11(const t11&) = default;

    t11& operator=(const t11&) = default;

    bool operator==(const t11& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11();
    }

    bool operator!=(const t11& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12> struct t12
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;

public:

    t12() = default;

    t12(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12) {}

    t12(const t12&) = default;

    t12& operator=(const t12&) = default;

    bool operator==(const t12& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12();
    }

    bool operator!=(const t12& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13> struct t13
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;

public:

    t13() = default;

    t13(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13) {}

    t13(const t13&) = default;

    t13& operator=(const t13&) = default;

    bool operator==(const t13& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13();
    }

    bool operator!=(const t13& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14> struct t14
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;
    T14 E14;

public:

    t14() = default;

    t14(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13, const T14& _e14) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13), E14(_e14) {}

    t14(const t14&) = default;

    t14& operator=(const t14&) = default;

    bool operator==(const t14& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13() && E14 == _tuple.e14();
    }

    bool operator!=(const t14& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13() || E14 != _tuple.e14();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }

    const T14& e14() const
    {
        return E14;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15> struct t15
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;
    T14 E14;
    T15 E15;

public:

    t15() = default;

    t15(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13, const T14& _e14, const T15& _e15) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13), E14(_e14), E15(_e15) {}

    t15(const t15&) = default;

    t15& operator=(const t15&) = default;

    bool operator==(const t15& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13() && E14 == _tuple.e14() && E15 == _tuple.e15();
    }

    bool operator!=(const t15& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13() || E14 != _tuple.e14() || E15 != _tuple.e15();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }

    const T14& e14() const
    {
        return E14;
    }

    const T15& e15() const
    {
        return E15;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15, typename T16> struct t16
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;
    T14 E14;
    T15 E15;
    T16 E16;

public:

    t16() = default;

    t16(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13, const T14& _e14, const T15& _e15, const T16& _e16) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13), E14(_e14), E15(_e15), E16(_e16) {}

    t16(const t16&) = default;

    t16& operator=(const t16&) = default;

    bool operator==(const t16& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13() && E14 == _tuple.e14() && E15 == _tuple.e15() &&
               E16 == _tuple.e16();
    }

    bool operator!=(const t16& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13() || E14 != _tuple.e14() || E15 != _tuple.e15() ||
               E16 != _tuple.e16();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }

    const T14& e14() const
    {
        return E14;
    }

    const T15& e15() const
    {
        return E15;
    }

    const T16& e16() const
    {
        return E16;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17> struct t17
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;
    T14 E14;
    T15 E15;
    T16 E16;
    T17 E17;

public:

    t17() = default;

    t17(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13, const T14& _e14, const T15& _e15, const T16& _e16, const T17& _e17) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13), E14(_e14), E15(_e15), E16(_e16), E17(_e17) {}

    t17(const t17&) = default;

    t17& operator=(const t17&) = default;

    bool operator==(const t17& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13() && E14 == _tuple.e14() && E15 == _tuple.e15() &&
               E16 == _tuple.e16() && E17 == _tuple.e17();
    }

    bool operator!=(const t17& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13() || E14 != _tuple.e14() || E15 != _tuple.e15() ||
               E16 != _tuple.e16() || E17 != _tuple.e17();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }

    const T14& e14() const
    {
        return E14;
    }

    const T15& e15() const
    {
        return E15;
    }

    const T16& e16() const
    {
        return E16;
    }

    const T17& e17() const
    {
        return E17;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18> struct t18
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;
    T14 E14;
    T15 E15;
    T16 E16;
    T17 E17;
    T18 E18;

public:

    t18() = default;

    t18(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13, const T14& _e14, const T15& _e15, const T16& _e16, const T17& _e17, const T18& _e18) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13), E14(_e14), E15(_e15), E16(_e16), E17(_e17), E18(_e18) {}

    t18(const t18&) = default;

    t18& operator=(const t18&) = default;

    bool operator==(const t18& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13() && E14 == _tuple.e14() && E15 == _tuple.e15() &&
               E16 == _tuple.e16() && E17 == _tuple.e17() && E18 == _tuple.e18();
    }

    bool operator!=(const t18& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13() || E14 != _tuple.e14() || E15 != _tuple.e15() ||
               E16 != _tuple.e16() || E17 != _tuple.e17() || E18 != _tuple.e18();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }

    const T14& e14() const
    {
        return E14;
    }

    const T15& e15() const
    {
        return E15;
    }

    const T16& e16() const
    {
        return E16;
    }

    const T17& e17() const
    {
        return E17;
    }

    const T18& e18() const
    {
        return E18;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19> struct t19
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;
    T14 E14;
    T15 E15;
    T16 E16;
    T17 E17;
    T18 E18;
    T19 E19;

public:

    t19() = default;

    t19(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13, const T14& _e14, const T15& _e15, const T16& _e16, const T17& _e17, const T18& _e18, const T19& _e19) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13), E14(_e14), E15(_e15), E16(_e16), E17(_e17), E18(_e18), E19(_e19) {}

    t19(const t19&) = default;

    t19& operator=(const t19&) = default;

    bool operator==(const t19& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13() && E14 == _tuple.e14() && E15 == _tuple.e15() &&
               E16 == _tuple.e16() && E17 == _tuple.e17() && E18 == _tuple.e18() && E19 == _tuple.e19();
    }

    bool operator!=(const t19& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13() || E14 != _tuple.e14() || E15 != _tuple.e15() ||
               E16 != _tuple.e16() || E17 != _tuple.e17() || E18 != _tuple.e18() || E19 != _tuple.e19();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }

    const T14& e14() const
    {
        return E14;
    }

    const T15& e15() const
    {
        return E15;
    }

    const T16& e16() const
    {
        return E16;
    }

    const T17& e17() const
    {
        return E17;
    }

    const T18& e18() const
    {
        return E18;
    }

    const T19& e19() const
    {
        return E19;
    }
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19, typename T20> struct t20
{
private:

    T1 E1;
    T2 E2;
    T3 E3;
    T4 E4;
    T5 E5;
    T6 E6;
    T7 E7;
    T8 E8;
    T9 E9;
    T10 E10;
    T11 E11;
    T12 E12;
    T13 E13;
    T14 E14;
    T15 E15;
    T16 E16;
    T17 E17;
    T18 E18;
    T19 E19;
    T20 E20;

public:

    t20() = default;

    t20(const T1& _e1, const T2& _e2, const T3& _e3, const T4& _e4, const T5& _e5, const T6& _e6, const T7& _e7, const T8& _e8, const T9& _e9, const T10& _e10,
        const T11& _e11, const T12& _e12, const T13& _e13, const T14& _e14, const T15& _e15, const T16& _e16, const T17& _e17, const T18& _e18, const T19& _e19, const T20& _e20) :
            E1(_e1), E2(_e2), E3(_e3), E4(_e4), E5(_e5), E6(_e6), E7(_e7), E8(_e8), E9(_e9), E10(_e10),
            E11(_e11), E12(_e12), E13(_e13), E14(_e14), E15(_e15), E16(_e16), E17(_e17), E18(_e18), E19(_e19), E20(_e20) {}

    t20(const t20&) = default;

    t20& operator=(const t20&) = default;

    bool operator==(const t20& _tuple) const
    {
        return E1 == _tuple.e1() && E2 == _tuple.e2() && E3 == _tuple.e3() && E4 == _tuple.e4() && E5 == _tuple.e5() &&
               E6 == _tuple.e6() && E7 == _tuple.e7() && E8 == _tuple.e8() && E9 == _tuple.e9() && E10 == _tuple.e10() &&
               E11 == _tuple.e11() && E12 == _tuple.e12() && E13 == _tuple.e13() && E14 == _tuple.e14() && E15 == _tuple.e15() &&
               E16 == _tuple.e16() && E17 == _tuple.e17() && E18 == _tuple.e18() && E19 == _tuple.e19() && E20 == _tuple.e20();
    }

    bool operator!=(const t20& _tuple) const
    {
        return E1 != _tuple.e1() || E2 != _tuple.e2() || E3 != _tuple.e3() || E4 != _tuple.e4() || E5 != _tuple.e5() ||
               E6 != _tuple.e6() || E7 != _tuple.e7() || E8 != _tuple.e8() || E9 != _tuple.e9() || E10 != _tuple.e10() ||
               E11 != _tuple.e11() || E12 != _tuple.e12() || E13 != _tuple.e13() || E14 != _tuple.e14() || E15 != _tuple.e15() ||
               E16 != _tuple.e16() || E17 != _tuple.e17() || E18 != _tuple.e18() || E19 != _tuple.e19() && E20 != _tuple.e20();
    }

    const T1& e1() const
    {
        return E1;
    }

    const T2& e2() const
    {
        return E2;
    }

    const T3& e3() const
    {
        return E3;
    }

    const T4& e4() const
    {
        return E4;
    }

    const T5& e5() const
    {
        return E5;
    }

    const T6& e6() const
    {
        return E6;
    }

    const T7& e7() const
    {
        return E7;
    }

    const T8& e8() const
    {
        return E8;
    }

    const T9& e9() const
    {
        return E9;
    }

    const T10& e10() const
    {
        return E10;
    }

    const T11& e11() const
    {
        return E11;
    }

    const T12& e12() const
    {
        return E12;
    }

    const T13& e13() const
    {
        return E13;
    }

    const T14& e14() const
    {
        return E14;
    }

    const T15& e15() const
    {
        return E15;
    }

    const T16& e16() const
    {
        return E16;
    }

    const T17& e17() const
    {
        return E17;
    }

    const T18& e18() const
    {
        return E18;
    }

    const T19& e19() const
    {
        return E19;
    }

    const T20& e20() const
    {
        return E20;
    }
};



