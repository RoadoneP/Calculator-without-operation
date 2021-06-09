#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define _CRT_SECUER_NO_WARNINGS 
#define ll long long
#define INT_MAX 
#define MAXBIT 64


ll XOR(ll x, ll y);
ll add (ll a, ll b);
ll sub (ll a, ll b);

bool isNegative(ll a);
bool isPositive(ll a);

// == 판단
bool iEqual(ll a, ll b) {
    if (a == b)
        return true;
    else
        return false;
}
// !=
bool UnEqual(ll a, ll b) {
    if (iEqual(a, b))
        return false;
    else
        return true;
}
// +1
ll iPlusOne(ll a) {
    return ++a;
}
// -1
ll iMinusOne(ll a) {
    return --a;
}
//left-shift
ll shift_arr[MAXBIT];
ll xor_arr[MAXBIT];

void _init_() {
    xor_arr[0] = 0;
    shift_arr[0] = 1;
    ll i = 0;
    while (UnEqual(i, MAXBIT)) {
        ll next_i = iPlusOne(i);
        xor_arr[next_i] =  XOR(xor_arr[i], shift_arr[i]);
        shift_arr[next_i] = iPlusOne(xor_arr[next_i]);
        i = next_i;
    }
    shift_arr[0] = 1;
}

ll LeftShift(ll a) {
    ll i = 0;
    ll rtn = 0;
    while (UnEqual(i, MAXBIT)) {
        ll next_i = iPlusOne(i);
        if (shift_arr[i] & a) {
            rtn |= shift_arr[next_i];
        }
        i = next_i;
    }
    return rtn;
}

ll RightShift(ll a) {
    ll i = MAXBIT;
    ll rtn = 0;
    while (UnEqual(i, 0)) {
        ll next_i = iMinusOne(i);
        if (shift_arr[i] & a) {
            rtn |= shift_arr[next_i];
        }
        i = next_i;
    }
    return rtn;
}


ll MultiRightShift(ll a, ll n) {
    ll i = 0;
    while (UnEqual(i, n)) {
        a = RightShift(a);
        i = iPlusOne(i);
    }
    return a;
}

ll MultiLeftShift(ll a, ll n) {
    ll i = 0;
    while (UnEqual(i, n)) {
        a = LeftShift(a);
        i = iPlusOne(i);
    }
    return a;
}

//~
ll NOT(ll x)
{
    ll res = 0;
    ll i = MAXBIT;

    while (UnEqual(i, -1))
    {

        bool b1 = x & MultiLeftShift(1, i);


        bool notBit = iEqual(b1, 1) ? 0 : 1;


        res = LeftShift(res);
        res |= notBit;
        i = iMinusOne(i);
    }
    //res = iPlusOne(res, 1);
    return res;
}
//&
//|

//양수 음수 
bool isNegative(ll a) {
    return (shift_arr[63] & a);
}

bool isPositive(ll a) {
    return iEqual(isNegative(a), 0);
}

//^
ll XOR(ll x, ll y)
{
    ll res = 0;
    ll i = MAXBIT;
   
    while(UnEqual(i,-1))
    {
     
        bool b1 = x & MultiLeftShift(1,i);
        bool b2 = y & MultiLeftShift(1,i);

        
        bool xoredBit = (b1 & b2) ? 0 : (b1 | b2);

      
        res = LeftShift(res);
        res |= xoredBit;
        i = iMinusOne(i);
    }
    return res;
}


// 더하기
ll add(ll a, ll b) {
    if (iEqual(b,0))
        return a;
    else return add(XOR(a,b), LeftShift(a&b));
}


//빼기
ll sub(ll a, ll b) {
    if (iEqual(b, 0))return a;
    else {
        return sub(XOR(a, b), LeftShift(NOT(a) & b));
    }
}

// 곱하기 (Russian Peasant 사용)
ll multiply(ll a, ll b)
{

    if (isNegative(b)) {
        b = add(NOT(b), 1);
        a = add(NOT(a), 1);
    }
    ll res = 0;

    while (UnEqual(b,0))
    {
        
        if (b & (ll) 1)
            res = add(res,a);


        a = LeftShift(a);
        b = RightShift(b);
        
    }
    return res;
}

//나누기
ll division(ll a, ll b) {
    ll c = 0, op = 0;

    if (isNegative(a)) {
        a = add(NOT(a), 1);
        op = XOR(op,1);
     
    }
    if (isNegative(b)) {
        b = add(NOT(b), 1);
        op = XOR(op, 1);

    }
    if (UnEqual(b,0)) {
        while (isPositive(sub(a,b))) {
            a = sub(a, b);
            c = add(c, 1);
        }
    }
    if (op)
        c = add(NOT(c), 1);
    return c;
}

int main() { //이경우에 문제가 생김
    _init_();
    
    printf("-----------------example---------------\n");
    printf("21474836400 + 21474836400 = %lld\n", add(21474836400, 21474836400));
    printf("-20 + 30 = %lld\n", add(-20, 30));
    printf("-20 + (-30) = %lld\n", add(-20, -30));
    printf("-21474836400 - 21474836400 = %lld\n", sub(-21474836400, 21474836400));
    printf("20 - 30 = %lld\n", sub(20, 30));
    printf("20 - (-30) = %lld\n", sub(20, -30));
    printf("30 / 3 = %lld\n", division(30, 3));
    printf("30 / -3 = %lld\n", division(30, -3));
    printf("-30 / -3 = %lld\n", division(-30, -3));
    printf("123456789 * 1000000 = %lld\n", multiply(123456789, 1000000));
    printf("------------------------------------------\n");
    
    while (true) {
        ll a = 0, b = 0;
        int c;
        printf("첫번째 정수 입력 : ");
        scanf("%lld", &a);
        printf("두번째 정수 입력 : ");
        scanf("%lld", &b);
        printf("더하기 1번\n");
        printf("빼기 2번\n");
        printf("곱하기 3번\n");
        printf("나누기 4번\n");
        printf("종료는 5번\n");

        scanf("%d", &c);

        switch (c)
        {
        case 1:
            printf("%lld + %lld = %lld\n", a, b, add(a, b));
            break;
        case 2:
            printf("%lld - %lld = %lld\n", a, b, sub(a, b));
            break;
        case 3:
            printf("%lld * %lld = %lld\n", a, b, multiply(a, b));
            break;
        case 4:
            printf("%lld / %lld = %lld\n", a, b, division(a, b));
            break;
        case 5:
            printf("End the program\n");
            return 0;
        default:
            printf("please enter the value again\n");
        }
    }
}