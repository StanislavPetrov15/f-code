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

