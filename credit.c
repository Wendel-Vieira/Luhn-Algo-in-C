#include <cs50.h>
#include <stdio.h>

long getPowerOf(int base, int exponent);

int count_digits(long n);
int sumDigits(int n);
int getLeadingDigits(long n, int len);
int getLuhnAlgoValue(long n, int len);

void printInvalidCard();
void printCardValidation(long n, int len);

void cardValidation(long n, int len);

int main(void)
{
    long card_n = get_long("Insert Card");
    int card_len = count_digits(card_n);

    if (card_len < 13 || card_len > 16)
    {
        printInvalidCard();
    }
    else
    {
        cardValidation(card_n, card_len);
    }
    return 0;
}

void cardValidation(long n, int len)
{
    // if last digit is zero, card is (possibly) valid
    bool isCardValid = (getLuhnAlgoValue(n, len) % 10) == 0;

    if (!isCardValid) // if falsy
    {
        printInvalidCard();
    }
    else
    {
        printCardValidation(n, len);
    }

}

int getLuhnAlgoValue(long n, int len)
{
    int sum = 0;

    // my luhns algo implementation
    for (int i = 0; i < len; i++)
    {
        int r;          // r stands for remainder
        if (i % 2 != 0) // if i is odd. Will only double second to last digit
        {
            r = (n % 10) * 2;
            sum += sumDigits(r);
        }
        else
        {
            sum += (n % 10);
        }
        n /= 10;
    }

    return sum;
}

int getLeadingDigits(long n, int len)
{ // math operation to get 10 to the power of size of card - 2
    long x = getPowerOf(10, len - 2);
    // here dividing the entire card num by x will get first two digits
    return n / x;
}

int count_digits(long n)
{
    int i = 0;
    while (n != 0)
    {
        n /= 10;
        i++;
    }
    return i;
}



int sumDigits(int n)
{
    int sum = 0;
    while (n > 0)
    {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

long getPowerOf(int base, int exponent)
{
    long result = 1;
    for (int i = 0; i < exponent; i++)
    {
        result *= base;
    }

    return result;
}

void printCardValidation(long n, int len)
{
    int a = getLeadingDigits(n, len); // a is first two leading digits

    if ((a > 50 && a < 56) && (len == 16))
    { // mastercards leading digits are between 50 and 57 and are always 16 digits long
        printf("MASTERCARD\n");
    }
    else if ((a / 10 == 4) && (len == 13 || len == 16))
    { // visacards first digit is always 4 and are either 13 or 16 digits long
        printf("VISA\n");
    }
    else if ((a == 34 || a == 37) && (len == 15))
    { // americanxcards leading digits are either 34 or 35 and is always 15 digits long
        printf("AMEX\n");
    }
    else
    { // if none of the above; card is invalid
        printInvalidCard();
    }
}

void printInvalidCard()
{
    printf("INVALID\n");
}
