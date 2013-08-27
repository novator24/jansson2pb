#include <fstream>
#include <iostream>
#include <test/test.pb.h>
#include <3party/jansson2pb.h>
#include <3party/jansson.h>
#include <time.h>
using namespace std;

int main(int argc,char *argv[])
{
 	// Test 1: read binary PB from a file and convert it to JSON
        std::string test1="test/test.dump";
	cout<<endl<<"TEST1: read "<<test1<<" and print as json"<<endl<<endl;
	{
		ifstream fin(test1.c_str(),ios::binary);
	        if(fin.good()) {
			google::protobuf::Message *p = new test::ComplexMessage();
			std::string x;
			while(fin.good()){
				std::string y;
	                        std::getline(fin, y);
				x = x + "\n" + y;
			}
			bool b;
int max = 1000000;

{
time_t start = time(0);
for(int z = 0; z < max; ++z) {
			b = p->ParseFromString(x);
}
time_t stop = time(0);
cout << "pb parse: " << (stop - start) << " / " << max << " = " << (double)(stop - start) / max << " seconds" << endl;
}

			if(!b) cout << "ERROR: failed to parse "<<test1<<endl;
{
time_t start = time(0);
for(int z = 0; z < max; ++z) {
			b = p->SerializeToString(&x);
}
time_t stop = time(0);
cout << "pb serialize: " << (stop - start) << " / " << max << " = " << (double)(stop - start) / max << " seconds" << endl;
}
			std::string s = pb2json(*p);
			cout<<s<<endl;
			delete p;
	       		cout<<endl<<"OK"<<endl<<endl;
		} else {
			cout<<"ERROR: "<<test1<<" not found"<<endl;
		}
	}

	// Test 2: convert PB to JSON directly
        std::string test2="";
	cout<<endl<<"TEST2: create pb object and print as json"<<endl<<endl;
	{
		test::ComplexMessage p2;
		p2.set__float(1);
		p2.set__str("a");
		p2.set__bin("b");
		p2.set__bool(true);
		std::string s2 = pb2json(p2);
		cout<<s2<<endl;
       		cout<<endl<<"OK"<<endl<<endl;
	}

	// Test 3
        std::string test3="test/test.json";
	cout<<endl<<"TEST3: read "<<test3<<" and convert to pb object"<<endl<<endl;
	{
		char buf[8192]; bzero(buf, 8192);
		FILE * fp = fopen(test3.c_str(), "r");
		if(fp) {
			size_t size = fread(buf, 1, 8192, fp);
			fclose(fp);
bool b = false;
json_t * root = 0;
json_error_t err;

int max = 1000000;

{
time_t start = time(0);
for(int z = 0; z < max; ++z) {
			if(root) free(root);
			root = json_loads(buf, 0, &err);
			b = (root != 0);
}
time_t stop = time(0);
cout << "json parse: " << (stop - start) << " / " << max << " = " << (double)(stop - start) / max << " seconds" << endl;
}

			if(!b) cout << "ERROR: failed to parse "<<test3<<endl;

{
time_t start = time(0);
for(int z = 0; z < max; ++z) {
			json_dumps(root, 0);
}
time_t stop = time(0);
cout << "json serialize: " << (stop - start) << " / " << max << " = " << (double)(stop - start) / max << " seconds" << endl;
}

			test::ComplexMessage msg;
			json2pb(msg, buf, size);
			//msg.SetExtension(test::e_bool, false);
			//printf("Message: %s\n", msg.DebugString().c_str());
			printf("%s\n", pb2json(msg).c_str());
	       		cout<<endl<<"OK"<<endl<<endl;
		} else {
			cout<<"ERROR: "<<test3<<" not found"<<endl;
		}
	}

	// Test 4
        std::string test4="test/test.dump";
	cout<<endl<<"TEST4: read "<<test4<<" as json and catch exception"<<endl<<endl;
	{
		char buf[8192];
		FILE * fp = fopen(test4.c_str(), "r");
		if(fp) {
			size_t size = fread(buf, 1, 8192, fp);
			fclose(fp);

			test::ComplexMessage msg;
			try {
				json2pb(msg, buf, size);
			} catch (j2pb_error& e) {
				cout << e.what() << endl;
			}
			//msg.SetExtension(test::e_bool, false);
			//printf("Message: %s\n", msg.DebugString().c_str());
			printf("%s\n", pb2json(msg).c_str());
	       		cout<<endl<<"OK"<<endl<<endl;
		} else {
			cout<<"ERROR: "<<test4<<" not found"<<endl;
		}
	}

	return 0;
}
