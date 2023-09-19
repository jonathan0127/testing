#include <bits/stdc++.h>
#define int long long
using namespace std;

// 計算 a^b mod n 的函數
int modpow(int a, int b, int n)
{
    int result = 1;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            result = (result * a) % n;
        }
        a = (a * a) % n;
        b = b / 2;
    }
    return result;
}

// 判斷一個數字是否為質數的函數
bool is_prime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    if (n <= 3)
    {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0)
    {
        return false;
    }
    int i = 5;
    while (i * i <= n)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return false;
        }
        i = i + 6;
    }
    return true;
}

// 找出兩個互質的數字的函數
int find_coprime(int n)
{
    int coprime = rand() % (n - 2) + 2;
    while (__gcd(coprime, n) != 1)
    {
        coprime = rand() % (n - 2) + 2;
    }
    return coprime;
}

// 找出d，使得ed ≡ 1 (mod φ(n))
int find_d(int e, int phi)
{
    int d = 1;
    while ((e * d) % phi != 1)
    {
        d++;
    }
    return d;
}

// 加密的函數
string encrypt(string plaintext, int e, int n)
{
    string ciphertext = "";
    for (int i = 0; i < plaintext.length(); i++)
    {
        int c = (int)plaintext[i];
        int encrypted = modpow(c, e, n);
        ciphertext += to_string(encrypted) + " ";
    }
    return ciphertext;
}

// 解密的函數
string decrypt(string ciphertext, int d, int n)
{
    string plaintext = "";
    stringstream ss(ciphertext);
    string token;
    while (getline(ss, token, ' '))
    {
        int c = stoi(token);
        int decrypted = modpow(c, d, n);
        plaintext += (char)decrypted;
    }
    return plaintext;
}

signed main()
{
    int func;
    cout << "請輸入要執行的操作：\n";
    cout << "1. 加密\n";
    cout << "2. 解密\n";
    cout << "0. 結束\n";
    cin >> func;
    cin.ignore();

    if(func == 1)
    {
        int func_2;
        cout << "1. 有公鑰\n";
        cout << "2. 沒有公鑰\n";
        cin >> func_2;
        cin.ignore();
        if(func_2 == 1)
        {
            // 讀取要加密的明文
            string plaintext;
            cout << "請輸入要加密的明文: ";
            getline(cin, plaintext);
            int e, n;
            cout << "請輸入公鑰: (e, n)";
            cin >> e >> n;
            // 加密
            string ciphertext = encrypt(plaintext, e, n);
            cout << "加密後的密文: " << ciphertext << '\n';
        }
        else if(func_2 == 2)
        {
            srand(time(NULL));

            // 選擇兩個不同的質數
            int p, q;
            do
            {
                p = rand() % 1000000 + 1;
            }
            while (!is_prime(p) || p < 10000); //使質數p >= 10000
            do
            {
                q = rand() % 1000000 + 1;
            }
            while (!is_prime(q) || p == q || q < 10000);

            // 計算 n 和 φ(n)
            int n = p * q;
            int phi = (p - 1) * (q - 1);

            // 選擇一個互質於 phi(n) 的整數 e，1 < e < φ(n)
            int e = find_coprime(phi);
            // 計算 d，使得 ed ≡ 1 (mod φ(n))
            int d = find_d(e, phi);

            cout << "公鑰: (" << e << ", " << n << ")" << '\n';
            cout << "私鑰: (" << d << ", " << n << ")" << '\n';




            // 讀取要加密的明文
            string plaintext;
            cout << "請輸入要加密的明文: ";
            getline(cin, plaintext);


            // 加密
            string ciphertext = encrypt(plaintext, e, n); // 以encrypt函式進行加密
            cout << "加密後的密文: " << ciphertext << '\n';

            // 解密
            string decryptedtext = decrypt(ciphertext, d, n); // 以decrypt函式進行解密
            cout << "解密後的明文: " << decryptedtext << '\n';
        }
    }
    else if(func == 2)
    {
        string ciphertext;
        cout << "請輸入要解密的密文: ";
        getline(cin, ciphertext);
        int d, n;
        cout << "請輸入私鑰: (d, n)";
        cin >> d >> n;
        cout << '\n';

        // 解密
        string decryptedtext = decrypt(ciphertext, d, n);
        cout << "解密後的明文: " << decryptedtext << '\n';
    }
    return 0;
}

