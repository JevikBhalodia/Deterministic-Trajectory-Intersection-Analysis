#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

#define ll long long 

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, x, y);
    if (g != 1) return -1;
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main() {

    ll L;
    ll a1, b1;
    ll a2, b2;

    //
    cout<< "Enter no of nodes you want to keep:\n";
    cin >> L;
    cout<< "Enter initial node and jump length for player 1\n";
    cin >> a1 >> b1;
    cout<< "Enter initial node and jump length for player 2\n";
    cin >> a2 >> b2;

    // if b1 is -ve then we have equivalent forward jump len of L - |b1|
    // if b1 is greater than L then we have equivalen b1 % L
    a1 = (a1 % L + L) % L;
    a2 = (a2 % L + L) % L;
    b1 = (b1 % L + L) % L;
    b2 = (b2 % L + L) % L;

    ll deltaA = a2 - a1;
    ll deltaB = b1 - b2;

    ll g = gcd(llabs(deltaB), L);

    // No solution case
    if (deltaA % g != 0) {
        cout << "They will never meet\n";
        return 0;
    }

    // Special case: same speed
    if (deltaB == 0) {
        if ((a1 - a2) % L == 0)
            cout << "They meet at time 0\n";
        else
            cout << "They will never meet\n";
        return 0;
    }

    // Special case: same initial node
    if (deltaA == 0) {
        // They meet at t = 0
        if (deltaB == 0) {
            cout << "They meet at time 0\n";
        } else {
            ll g = gcd(llabs(deltaB), L);
            ll t = L / g;   // first positive meeting time
            cout << "They meet at time " << t << "\n";
        }
        return 0;
    }


    // Reduce equation
    ll A = deltaA / g;
    ll B = deltaB / g;
    ll M = L / g;

    // Normalize B
    B = (B % M + M) % M;

    ll invB = mod_inverse(B, M);

    
    ll t0 = ( (A % M + M) % M * invB ) % M;
    
    // tk = t0 + k*M, they will meet at k = 0,1,2,3...
    if(t0 == 0) t0 += M;

    cout << "They meet at time " << t0 << "\n";

    return 0;
}
