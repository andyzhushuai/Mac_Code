#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
class shaizi
{
	public:
		    int getdian();
	private:
			  int dian;
};
int main()
{
	    shaizi *s1 = new shaizi();
			cout << "摇出的点数" <<s1->getdian()<<endl;
			return 0;
			delete s1;
}
int shaizi::getdian()
{
	    srand(time(0));
			dian=rand()%6+1;
			return dian;
}

