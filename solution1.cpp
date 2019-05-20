/*

It's my solution for:
https://www.youtube.com/watch?v=GBuHSRDGZBY
(First problem)

I know this is not so good code but if u want to read other
people code to ¿learn? just take it :)
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct pair_t {
   int a, b;
};

struct closests_t {
   bool usingVector;
   vector<pair_t> vec;
   pair_t c_pair;
};

inline int diff(int a, int b) { return abs(a - b); }

unsigned char compare(int a, int b)
{
   if (a > b) return -1;
   if (a < b) return 1;
   return 0;
}

template <int f, int c>
closests_t * getClosests(const int matrix[f][c], int number)
{
   closests_t * closests = new closests_t;
   closests->c_pair = { -1, -1 };
   closests->usingVector = false;

   for (int i = 0; i < c; i++)
   {
      for (int j = 0; j < c; j++)
      {
         if (closests->c_pair.a == -1 && !closests->usingVector)
         {
            closests->c_pair = {
               matrix[0][i],
               matrix[1][j]
            };
            continue;
         }

         if (!closests->usingVector)
         {
            int comparation = compare(
               diff(matrix[0][i] + matrix[1][j], number),
               diff(closests->c_pair.a + closests->c_pair.b, number)
            );

            if (comparation == 1) // compare(int, int) returns 1 if the 1st param is less than 2nd
            {
               closests->c_pair = {
                  matrix[0][i],
                  matrix[1][j]
               };
               continue;
            }

            if (!comparation) // There are more than one pair that is close
            { // Start using vector
               closests->usingVector = true;
               closests->vec.push_back( { closests->c_pair.a, closests->c_pair.b } ); // pass the VALUES to the vector (it can be changed to pass the indexes)
               closests->vec.push_back( { matrix[0][i], matrix[1][j] } );
               closests->c_pair = { -1, -1 };
            }
            continue;
         }

         //  If using vector compare with the first element

         int comparation = compare(
               diff(matrix[0][i] + matrix[1][j], number),
               diff(closests->vec[0].a + closests->vec[0].b, number)
         );

         if (comparation == 1)
         {
            closests->usingVector = false;
            closests->vec.clear();
            closests->c_pair = { matrix[0][i], matrix[1][j] };
         }
         continue;
      }
   }
   return closests;
}

int main()
{
   const int matrix[][15] = {
      { 12, 43, 61, 13, 19, 54, 34, 53, 23, 42, 12, 85, 33, 35, 64 },
      { 23, 14, 16, 44, 53, 231, 122, 74, 13, 43, 64, 26, 11, 6, 2}
   };

   closests_t * closests = getClosests<2, 15>(matrix, 122);

   if (!closests->usingVector) cout << closests->c_pair.a << ", " << closests->c_pair.b;
   else
   {
      for (int i = 0; i < closests->vec.size(); i++)
      {
         cout << closests->vec[i].a << ", " << closests->vec[i].b << endl;
      }
   }
   
   return 0;
}