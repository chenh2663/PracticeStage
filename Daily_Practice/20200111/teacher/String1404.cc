#include <stdio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


void test()
{
    string s1("hello");
    string s2 = s1;

    cout << "s1 = " << s1 <<endl;
    cout << "s2 = " << s2 <<endl;

    printf("s1's address : %p\n",s1.c_str());
    printf("s2's address : %p\n",s2.c_str());
    string s3 = "world";
    cout << "s1 = " << s1 <<endl;
    cout << "s2 = " << s2 <<endl;
    cout << "s3 = " << s3 <<endl;

    printf("s1's address : %p\n",s1.c_str());
    printf("s2's address : %p\n",s2.c_str());
    printf("s3's address : %p\n",s3.c_str());
    cout << endl;
    s3 = s1;
    cout << "s1 = " << s1 <<endl;
    cout << "s2 = " << s2 <<endl;
    cout << "s3 = " << s3 <<endl;

    printf("s1's address : %p\n",s1.c_str());
    printf("s2's address : %p\n",s2.c_str());
    printf("s3's address : %p\n",s3.c_str());

    cout << endl;
    s3[0] = 'H';
    cout << "s3[0] = " << s3[0] <<endl;
    cout << "s1 = " << s1 <<endl;
    cout << "s2 = " << s2 <<endl;
    cout << "s3 = " << s3 <<endl;

    printf("s1's address : %p\n",s1.c_str());
    printf("s2's address : %p\n",s2.c_str());
    printf("s3's address : %p\n",s3.c_str());
}
int main(int argc, char **argv)
{
    test();
    return 0;
}

