#include <iostream>
#include <fstream>
#include <json.h>

#pragma comment(lib, "lib_json.lib")

using namespace std;


int main()
{
	ifstream ifs;
	ifs.open("test.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false))
	{
		return -1;
	}

	Json::Value &add_value = root["address"];
	Json::Value append_value;
	append_value["name"] = "append";
	append_value["email"] = "append@163.com";
	add_value.append(append_value);

	Json::Value &change_value = add_value[1];
	change_value["name"] = Json::Value("zoujiemeng");
	change_value["email"] = Json::Value("zzz-oo-u@163.com");

	add_value[2].removeMember("name");

	for (int i = 0; i < add_value.size(); ++i)
	{
		Json::Value temp_value = add_value[i];
		string strName = temp_value["name"].asString();
		string strMail = temp_value["email"].asString();
		cout << "name: " << strName << " email: " << strMail << endl;
	}

	Json::FastWriter writer;
	string json_append_file = writer.write(root);
	string strOut = root.toStyledString();
	ofstream ofs;
	ofs.open("test_append.json", 'w');
	ofs << json_append_file;
	ofs << strOut;

	system("pause");
	return 0;
}

#if 0


	ifstream ifs;
	ifs.open("test.json");

	Json::Reader reader;
	Json::Value root;
	if(!reader.parse(ifs, root, false))
	{
		return -1;
	}
	Json::Value add_value = root["address"];
	for (std::size_t i = 0; i < add_value.size(); ++i)
	{
		Json::Value temp_value = add_value[i];
		string strName = temp_value["name"].asString();
		string strMail = temp_value["email"].asString();
		cout << "name: " << strName << " email: " << strMail << endl;
	}



	WriteJsonData("test.json");
void WriteJsonData(const char* filename)
{
	Json::Reader reader;
	Json::Value root;
	/*ifstream is;*/
	/*is.open(filename, std::ios::binary);
	if (reader.parse(is, root, false))
	{*/
		Json::Value item;
		root["key"] = "value1";
		item["arrayKey"] = 2;
		root["array"].append(item);

		Json::FastWriter writer;
		string strWrite = writer.write(root);
		ofstream ofs;
		ofs.open(filename, 'w');
		ofs << strWrite;
		ofs.close();
		/*}
		is.close()*/;
}

	Json::Value root;
	Json::Value arrayObj;
	Json::Value item;

	root["key"] = "value1";
	for (int i = 0; i < 10; ++i)
	{
		item["arrayKey"] = i;
		arrayObj.append(item);
	}
	root["array"] = arrayObj;
	std::string out = root.toStyledString();
	std::cout << out << std::endl;




	const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";

	Json::Reader reader;
	Json::Value root;
	if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		std::string upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"  
		int code = root["code"].asInt();    // 访问节点，code = 100 
		cout << "upload_id: " << upload_id << endl;
		cout << "code: " << code << endl;
	}

#endif