#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int extendedGCD(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = extendedGCD(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int modInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, x, y);
    if (gcd != 1) return -1; // No modular inverse if not coprime
    return (x % m + m) % m;  // Ensure positive result
}

void affineCipher(string &text, int a, int b, bool encrypt) {
    for (char &ch : text) {
        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            if (encrypt) {
                ch = (a * (ch - base) + b) % 26 + base;
            } else {
                int aInverse = modInverse(a, 26);
                if (aInverse == -1) {
                    cerr << "Error: 'a' and 26 are not coprime.\n";
                    return;
                }
                ch = (aInverse * (ch - base - b + 26)) % 26 + base;
            }
        }
    }
}

int main() {
    string message;
    int a, b;

    cout << "Enter the text to be ciphered/deciphered: ";
    getline(cin, message);

    cout << "Enter the key 'a' (coprime with 26): ";
    cin >> a;

    cout << "Enter the key 'b': ";
    cin >> b;

    affineCipher(message, a, b, true);
    cout << "Affine ciphered message: " << message << endl;

    affineCipher(message, a, b, false);
    cout << "Decrypted message: " << message << endl;

    return 0;
}
