#include <iostream>
#include <chrono>

using namespace std; 

#define FIRSTDATATYPE unsigned long int // choose a data type here
#define SECONDDATATYPE unsigned short int// choose a data type here

FIRSTDATATYPE gcd(FIRSTDATATYPE a, FIRSTDATATYPE b) {
  return b == 0 ? a : gcd(b, a % b);
}

class RSA 
{
private:
  SECONDDATATYPE p;
  SECONDDATATYPE q;
  FIRSTDATATYPE d;
public:
  FIRSTDATATYPE e;
  FIRSTDATATYPE n;
  RSA(SECONDDATATYPE p, SECONDDATATYPE q) : p(p), q(q)
  {
	  n =(FIRSTDATATYPE) p * (FIRSTDATATYPE) q;
	  FIRSTDATATYPE phi_n = ((FIRSTDATATYPE) p - 1) * ((FIRSTDATATYPE) q - 1);
	  e = 2;
	  while (gcd(e, phi_n) != 1)
	  {
		  e++;
	  }
	  d = 1;
	  while (((unsigned long long) e * (unsigned long long) d) % phi_n != 1)
	  {
		  d++;
	  }
  }

  FIRSTDATATYPE encrypt(FIRSTDATATYPE m)
  {
	  FIRSTDATATYPE result = 1;
	  for (int i = 0; i < e; i++)
	  {
			result = (unsigned long long) result * (unsigned long long) m % n;
	  }
	  return result;
  }

  FIRSTDATATYPE decrypt(FIRSTDATATYPE c)
  {
	  FIRSTDATATYPE result = 1;
	  for (int i = 0; i < d; i++)
	  {
			result = (unsigned long long) result * (unsigned long long) c % n;
	  }
	  return result;
  }

  FIRSTDATATYPE decrypt_bit(FIRSTDATATYPE c)
  {
	  FIRSTDATATYPE result = 1;
	  FIRSTDATATYPE a = 1 << 31;

	  for (int i = 0; i < sizeof(a)*8; i++)
	  {
		  if (d & a) //if we encounter 1
		  {
			  result = (unsigned long long) result * (unsigned long long) c % n;
		  }
		  if (i != (sizeof(a)*8) -1)
		  {
			  result = (unsigned long long) result * (unsigned long long) result % n;
		  }
		  a = a >> 1;
	  }
	  return result;
  }
};


int main () {

  RSA rsa(62137, 62141);
  //RSA rsa(5, 11);
  
  auto start = std::chrono::system_clock::now();
  FIRSTDATATYPE c = rsa.encrypt(15);
  auto end = std::chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end - start;
  time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << "Encryption time: " << elapsed_seconds.count() << "s -- " << " ciphertext is " << c << "\n";

  start = std::chrono::system_clock::now();
  FIRSTDATATYPE m = rsa.decrypt(c);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  end_time = std::chrono::system_clock::to_time_t(end);
  cout << "Decryption time: " << elapsed_seconds.count() << "s -- " << " message is " << m << "\n";

  start = std::chrono::system_clock::now();
  FIRSTDATATYPE m_bit = rsa.decrypt_bit(c);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end - start;
  end_time = std::chrono::system_clock::to_time_t(end);
  cout << "Decryption time: " << elapsed_seconds.count() << "s -- " << " message is " << m_bit << "\n";



  return 0;
}