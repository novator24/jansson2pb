#include <fstream>
#include <iostream>
#include <test/test.pb.h>
#include <3party/jansson2pb.h>

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
			bool b = p->ParseFromIstream(&fin);
			if(!b) cout << "ERROR: failed to parse "<<test1<<endl;
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
		char buf[8192];
		FILE * fp = fopen(test3.c_str(), "r");
		if(fp) {
			size_t size = fread(buf, 1, 8192, fp);
			fclose(fp);

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
