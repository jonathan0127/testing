#include <bits/stdc++.h>
#define int long long
using namespace std;

// �p�� a^b mod n �����
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

// �P�_�@�ӼƦr�O�_����ƪ����
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

// ��X��Ӥ��誺�Ʀr�����
int find_coprime(int n)
{
    int coprime = rand() % (n - 2) + 2;
    while (__gcd(coprime, n) != 1)
    {
        coprime = rand() % (n - 2) + 2;
    }
    return coprime;
}

// ��Xd�A�ϱoed �� 1 (mod �p(n))
int find_d(int e, int phi)
{
    int d = 1;
    while ((e * d) % phi != 1)
    {
        d++;
    }
    return d;
}

// �[�K�����
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

// �ѱK�����
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
    cout << "�п�J�n���檺�ާ@�G\n";
    cout << "1. �[�K\n";
    cout << "2. �ѱK\n";
    cout << "0. ����\n";
    cin >> func;
    cin.ignore();

    if(func == 1)
    {
        int func_2;
        cout << "1. �����_\n";
        cout << "2. �S�����_\n";
        cin >> func_2;
        cin.ignore();
        if(func_2 == 1)
        {
            // Ū���n�[�K������
            string plaintext;
            cout << "�п�J�n�[�K������: ";
            getline(cin, plaintext);
            int e, n;
            cout << "�п�J���_: (e, n)";
            cin >> e >> n;
            // �[�K
            string ciphertext = encrypt(plaintext, e, n);
            cout << "�[�K�᪺�K��: " << ciphertext << '\n';
        }
        else if(func_2 == 2)
        {
            srand(time(NULL));

            // ��ܨ�Ӥ��P�����
            int p, q;
            do
            {
                p = rand() % 1000000 + 1;
            }
            while (!is_prime(p) || p < 10000); //�Ͻ��p >= 10000
            do
            {
                q = rand() % 1000000 + 1;
            }
            while (!is_prime(q) || p == q || q < 10000);

            // �p�� n �M �p(n)
            int n = p * q;
            int phi = (p - 1) * (q - 1);

            // ��ܤ@�Ӥ���� phi(n) ����� e�A1 < e < �p(n)
            int e = find_coprime(phi);
            // �p�� d�A�ϱo ed �� 1 (mod �p(n))
            int d = find_d(e, phi);

            cout << "���_: (" << e << ", " << n << ")" << '\n';
            cout << "�p�_: (" << d << ", " << n << ")" << '\n';




            // Ū���n�[�K������
            string plaintext;
            cout << "�п�J�n�[�K������: ";
            getline(cin, plaintext);


            // �[�K
            string ciphertext = encrypt(plaintext, e, n); // �Hencrypt�禡�i��[�K
            cout << "�[�K�᪺�K��: " << ciphertext << '\n';

            // �ѱK
            string decryptedtext = decrypt(ciphertext, d, n); // �Hdecrypt�禡�i��ѱK
            cout << "�ѱK�᪺����: " << decryptedtext << '\n';
        }
    }
    else if(func == 2)
    {
        string ciphertext;
        cout << "�п�J�n�ѱK���K��: ";
        getline(cin, ciphertext);
        int d, n;
        cout << "�п�J�p�_: (d, n)";
        cin >> d >> n;
        cout << '\n';

        // �ѱK
        string decryptedtext = decrypt(ciphertext, d, n);
        cout << "�ѱK�᪺����: " << decryptedtext << '\n';
    }
    return 0;
}

