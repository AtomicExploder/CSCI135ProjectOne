#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream studentdata;
	studentdata.open ("StudentData.tsv");
	ifstream huntercourses;
	huntercourses.open("HunterCourses.tsv");
	ofstream studentdataplus;
	studentdataplus.open("StudentDataPlus.tsv");
	ofstream studentsummary;
	studentsummary.open("StudentSummary.tsv");
		
	string subject,catalog_number, designation_code, empl_id, semester, subject_code, catalog_code, letter_grade;
	double contact_hours, numeric_grade, numeric_grade2;
	bool hours_desginationcode_finder;


	//this line loops through StudentData
	while(studentdata>>empl_id>>semester>>subject_code>>catalog_code>>letter_grade>>numeric_grade)
	{
		//this lines adds StudentData line to StudentDataPlus
		studentdataplus << empl_id << "	" << semester << "	" << subject_code << "	" << catalog_code << "	" << letter_grade << "	" << numeric_grade;

		//this segment finds the hours and corresponding designation code
		hours_desginationcode_finder = 0; 
		//this boolean is set to false each time to ensure we find hours/designation code for each student
		while(huntercourses>>subject>>catalog_number>>contact_hours>>designation_code)
		{	
			if(subject_code == subject && catalog_code == catalog_number) 
			{
				//Once the program has found a match in HunterCourses, the program will add it to StudentDataPlus 
				studentdataplus << "	" << contact_hours << "	" <<  designation_code << endl;
				hours_desginationcode_finder = 1;
				huntercourses.close();
				huntercourses.open("HunterCourses.tsv");
				break;
				//once the program finds a match, it break out of the loop
			}

		}

		//this segment checks if hours and corresponding designation code has been added for the current line
		if(hours_desginationcode_finder == 0)
		{
			//if the program sees that nothing is added yet, it will just add 3.0 RNL
			studentdataplus << "	" << "3.0" << "	" << "RNL" << endl;
			huntercourses.close();
			huntercourses.open("HunterCourses.tsv");
			// I am closing and reopening the file so that when it opens up again, it loops back to the first line
		}
	}
	

	studentdataplus.close();
	huntercourses.close();
	ifstream studentdataplus2;
	studentdataplus2.open("StudentDataPlus.tsv");

	int Total_Classes=0, Total_CSCI_Classes=1;
	double Total_GPA = 0, Total_CSCI_GPA=0, Total_Contact_Hours=0, Total_CSCI_Contact_Hours=0;
	//here I am initializing new variables for the second part of this project
	string empl_id_checker;
	studentdataplus2>>empl_id>>semester>>subject_code>>catalog_code>>letter_grade>>numeric_grade>>contact_hours>>designation_code;
	empl_id_checker = empl_id;
	empl_id = empl_id;
	Total_GPA= Total_GPA+ numeric_grade;
	Total_CSCI_GPA = Total_CSCI_GPA+numeric_grade;
	Total_Contact_Hours = Total_Contact_Hours +contact_hours;
	Total_CSCI_Contact_Hours = Total_CSCI_Contact_Hours +contact_hours;
	Total_Classes ++;
	studentsummary << empl_id << "	";
	while(studentdataplus2>>empl_id>>semester>>subject_code>>catalog_code>>letter_grade>>numeric_grade>>contact_hours>>designation_code)
	{
		//here it is checking studentdataplus line for line
		if(empl_id == empl_id_checker)
		//here it is checking over each invidivual student or empl_id and doing it until it changes to the next ID.
		{
			Total_Contact_Hours = Total_Contact_Hours + contact_hours;
			numeric_grade2 = numeric_grade;
			Total_Classes++;
			empl_id = empl_id;
			numeric_grade2 = numeric_grade;
			//this segment below checks the classes for which a student has had CSCI and taking the total GPA and the amount of classes that student had, exlcuding the ones with a -1.
			if(subject_code == "CSCI")
			{
					if (numeric_grade == -1)
					{
						numeric_grade2 = 0;
						Total_CSCI_Classes --;   
					}	
				Total_CSCI_GPA = Total_CSCI_GPA + numeric_grade2;
				Total_CSCI_Classes++;
			}
			//this segment below is finding the designation codes for each student of RNL, MNL and GNL and adding up the contact hours.
			if(designation_code == "RNL" || designation_code == "MNL" || designation_code == "GNL")
			{
				Total_CSCI_Contact_Hours = Total_CSCI_Contact_Hours + contact_hours;
			}
			if(numeric_grade == -1)
			{
				numeric_grade = 0;
				Total_Classes --;
			}
			Total_GPA= Total_GPA + numeric_grade;
		}
		else
		//in this segment below is really where the ending calculations happen such as the overall GPA average, the overall CSCI average, and the percentage of time spent taking non-liberal arts courses.
		{
			studentsummary << "	"<< Total_GPA/Total_Classes <<"	"  << "	"<< Total_CSCI_GPA/Total_CSCI_Classes <<"	" << (Total_CSCI_Contact_Hours/Total_Contact_Hours)*100 << "%" << endl;
			studentsummary << empl_id << "	";
			Total_GPA =0;
			Total_Classes = 0;
			Total_Classes++;
			Total_CSCI_GPA =0;
			Total_CSCI_Classes = -1;
			Total_CSCI_Classes++;
			Total_Contact_Hours = contact_hours;
			if(designation_code == "RNL" || designation_code == "MNL" || designation_code == "GNL")
			{
				Total_CSCI_Contact_Hours = contact_hours;
			}
			else
			{
				Total_CSCI_Contact_Hours = 0;
			}
		}
		empl_id_checker = empl_id;

	}
	studentsummary <<  "	" << Total_GPA/Total_Classes << "	"  <<  "	"<< Total_CSCI_GPA/Total_CSCI_Classes << "	" << (Total_CSCI_Contact_Hours/Total_Contact_Hours)*100 << "%" << endl;
	studentdataplus2.close();
	return 0;
}