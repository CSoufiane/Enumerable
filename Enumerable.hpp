//Author: Soufiane
#ifndef __SFN_ENUMERABLE_
#define __SFN_ENUMERABLE_

#include <functional>
#include <iostream>
namespace SFN
{

    #define ENUMERABLE(T, scope, body) Enumerable<T> (scope (std::function<void(T)> run) body)

    template<typename T>
    class Enumerable
    {
    private:
        std::function<void (std::function<void(T)>)> _looper; 
    public:
        Enumerable(std::function<void (std::function<void(T)>)> looper):_looper(looper)
        {
        }
        static Enumerable<T> Range(T t1, T t2)
        {
            return ENUMERABLE(T,[=],{ for(T t = t1; t < t2; ++t) run(t); });
        }
        Enumerable(const Enumerable<T>& e):_looper(e._looper)
        {
        }
        Enumerable<T> operator=(const Enumerable<T>& e)
        {
            _looper = e._looper;
            return *this;
        }
        void Foreach(std::function<void (T)> f) const
        {
            _looper(f);
        };
        void Run() const
        {
            auto _void = [](T) -> void {};
            Foreach(_void);
        }
        Enumerable<T> Where(std::function<bool(T)> condition) const
        {
            const Enumerable<T>& data = *this;
            return Enumerable<T> ([=] (std::function<void(T)> run)
            {
                auto filter = [=](T t) -> void
                {
                    if(condition(t))
                        run(t);
                };
                data.Foreach(filter);
            });
        }
        Enumerable<T> Do(std::function<void(T)> extraWork) const
        {
            const Enumerable<T>& data = *this;
            return Enumerable<T> ([=] (std::function<void(T)> run)
            {
                auto filter = [=](T t) -> void
                {
                    extraWork(t);
                    run(t);
                };
                data.Foreach(filter);
            });
        }
        template<typename U>
        Enumerable<U> Select(std::function<U(T)> transform) const
        {
            const Enumerable<T>& data = *this;
            return Enumerable<U> ([=] (std::function<void(U)> run)
            {
                auto filter = [=](T t) -> void
                {
                    run(transform(t));
                };
                data.Foreach(filter);
            });
        }

        Enumerable<T> Select(std::function<T(T)> transform) const
        {
            return Select<T>(transform);
        }
        Enumerable<T> Take(unsigned int n)
        {
            class _STOP_TO_COMPUTE_{};
            const Enumerable<T>& data = *this;
            return Enumerable<T> ([=] (std::function<void(T)> run)
            {
                auto stop = n;
                auto computer = [=](T t) mutable -> void
                {
                    if(stop<=0)
                        throw _STOP_TO_COMPUTE_();
                    --stop;
                    run(t);
                };
                try
                {
                    data.Foreach(computer);
                }catch(_STOP_TO_COMPUTE_&) {}
            });
        }    
    };

}

#endif
