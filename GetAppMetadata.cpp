#include<iostream>
#include<cstdlib>
#include<fstream>
using namespace std;

int main(int arc,char * argv[])
{
	if(arc!=3)
	{
		cout<<"Error: the number of arguments is not right"<<endl;
		system("PAUSE"); 
		return -1;	
	}
    
	string str_category=argv[1];// such as  books_and_reference
	int int_pages=atoi(argv[2]);	// the number of loops
	if(int_pages>10) 
	{
		cout<<"Error: the max number of pages is 10"<<endl;
		system("PAUSE"); 
		return -1;	
	}
	
	
	int AppNum=0; // the number of apks
	string href[1000]; // save the download_url of apks
	string app_size[1000]; // save the file size of apks
	string app_name[1000];
	string Author[1000];
	string Latest_Version[1000];
	string Publish_Date[1000];
	string Requirements[1000];

    // some strings for creating a command 
	string str_curl="curl-7.46.0-win32-mingw\\bin\\curl ";
	string str1="https://apkpure.com/";
	string str2="?page=";
	string str3=" > pages\\page";
	string str4=".html";
	string str5="pages\\page";


	int number=0;
	while(number<int_pages) 
	{
		number++;	
        char PageNumber[10];
        sprintf(PageNumber,"%d",number);
			
		// Get the  web page
        // the format of command: 
		// curl https://apkpure.com/books_and_reference?page=1 > pages\page1.html	
		string command=str_curl+str1+str_category+str2+PageNumber+str3+PageNumber+str4;
		system(command.c_str()); // Excuting a command
		
		ifstream fin((str5+PageNumber+str4).c_str());//  Open file : pages\page1.html
		if(!fin)
		{
			cout<<"Open File Fail";
			system("PAUSE");
			return -1;
		}	
						
		while(!fin.eof()) // Analysis the web page
		{
			char line[100000];
			fin.getline(line,100000,'\n');
			string str=line;
			if(str.find("category-template-img")!=string::npos)// if we find the Substring, we get a detailed web page 
 			{
					int pos1=str.find("href=");
					int pos2=str.find("img alt=");
					string new_url;
					new_url=str.substr(pos1+6,(pos2-3)-(pos1+6));
					new_url="https://apkpure.com"+new_url;

					char ApkNumber[10];
					sprintf(ApkNumber,"%d",AppNum%20+1);// There are 20 apks on each page
					string filename="pages\\page"+string(PageNumber)+"_"+string(ApkNumber)+".html";
					// format: curl https://apkpure.com/google-play-books/com.google.android.apps.books > pages\page1_1.html
					string command=str_curl+new_url+" > "+filename;
					system(command.c_str());  // Excuting a command
					
					ifstream fin1(filename.c_str());
					if(!fin1)
					{
					cout<<"Open File Fail";
					system("PAUSE");
					return -1;
					}
					
					app_size[AppNum]="null"; //
					app_name[AppNum]="null";//
					Author[AppNum]="null";//
					Latest_Version[AppNum]="null";
 					Publish_Date[AppNum]="null";
 					Requirements[AppNum]="null";

					while(!fin1.eof()) // Analysis the secondary page
					{	

						
						fin1.getline(line,100000,'\n');
						string str_tmp=line;
						
						//App Name
						if(str_tmp.find("<title>")!=string::npos) //i.4
						{
							pos1=str_tmp.find("<title>");
							pos2=str_tmp.find("APK Download");
							app_name[AppNum]=str_tmp.substr(pos1+7,(pos2-1)-(pos1+7));
							//cout<<endl<<app_name[AppNum]<<"---------"<<endl;							
							
						}
						
						//Author
						else if(str_tmp.find("<span itemprop=\"name\">")!=string::npos) //i.335
						{
							pos1=str_tmp.find("<span itemprop=\"name\">");
							pos2=str_tmp.find("</span></a></p>");
							Author[AppNum]=str_tmp.substr(pos1+22,pos2-(pos1+22));							
						}		
						
						//Latest_Version 
						else if(str_tmp.find("softwareVersion")!=string::npos)  //i.339
						{
							pos1=str_tmp.find("<p itemprop=\"softwareVersion\">");
							pos2=str_tmp.find("</p>");
							Latest_Version[AppNum]=str_tmp.substr(pos1+30,pos2-(pos1+30));
														
						}							
						
						//Publish_Date
						else if(str_tmp.find("datePublished")!=string::npos)  //i.344
						{
							pos1=str_tmp.find("<p itemprop=\"datePublished\">");
							pos2=str_tmp.find("</p>");
							Publish_Date[AppNum]=str_tmp.substr(pos1+28,pos2-(pos1+28));							
						}
						
						//Requirements
						else if(str_tmp.find("operatingSystem")!=string::npos)  //i.339
						{
							pos1=str_tmp.find("<p itemprop=\"operatingSystem\">");
							pos2=str_tmp.find("</p>");
							Requirements[AppNum]=str_tmp.substr(pos1+30,pos2-(pos1+30));							
						}	
						
						//App Size
						else if(str_tmp.find("Download APK (")!=string::npos) //i.466
						{
							pos1=str_tmp.find("nload AP");
							pos2=str_tmp.find("/a></");
							app_size[AppNum]=str_tmp.substr(pos1+11,(pos2-2)-(pos1+11));
							break;// the last one
						}
					}
					
			}
			else if(str.find("category-template-down")!=string::npos)//if we find the Substring, we get the download_url of apk
 			{
			    if(str.find("Download XAPK")==string::npos)
			    {
					int pos1=str.find("href=");
					int pos2=str.find("Download APK");
					href[AppNum]=str.substr(pos1+6,(pos2-2)-(pos1+6));
	
				}
				else 
				href[AppNum]="null";
			    
				AppNum++;// only size++
				if(AppNum>1000) return -1;
			}
		
		}
		fin.close(); // close the file		
	}//loop end
    
    
    //Creating  txt and csv
    str1="pages\\AppMetadata_";
    str2=str_category;
    str3=".txt";
    str4=str1+str2+str3; // 
    ofstream fout(str4.c_str());
 	for(int i=0;i<AppNum;i++)
 	{
		//cout<<app_name[i]<<" "<<Latest_Version[i]<<endl; system("PAUSE");
		fout<<app_name[i];
		fout<<";"<<str_category<<";"<<Latest_Version[i]<<";"<<Publish_Date[i]<<";"<<Requirements[i]<<";"<<app_size[i]<<";"<<Author[i]<<";"<<href[i]<<endl;
	} 
    fout.close();
    				 
	str3=".csv";
	str4=str1+str2+str3; // 
	fout.open(str4.c_str());
 	for(int i=0;i<AppNum;i++)
 	{
		fout<<"\"";		fout<<app_name[i];		fout<<"\"";
		fout<<",";
		fout<<str_category;
		fout<<",";	
		fout<<"\"";		fout<<Latest_Version[i];		fout<<"\"";
		fout<<",";
		fout<<"\"";		fout<<Publish_Date[i];		fout<<"\"";
		fout<<",";
		fout<<"\"";		fout<<Requirements[i];		fout<<"\"";
		fout<<",";
		fout<<app_size[i];
		fout<<",";
		fout<<"\"";		fout<<Author[i];		fout<<"\"";
		fout<<",";
		fout<<href[i];
		fout<<endl;
	} 
    fout.close();


    cout<<endl<<endl<<"Completed."<<endl; 

	return 0;
}


