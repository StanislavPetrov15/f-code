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

