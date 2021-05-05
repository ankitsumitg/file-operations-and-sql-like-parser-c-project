# file-operations-and-sql-like-parser-c-project
File operations in c and implementing sql like query parser using csv files.
- Simple query handler
	1 Query format example: select * from student where exam1 gt 50
	* Note1:For now only works with student structure and query whould in proper format with no extra spaces
	* Note2:CAn only display single or total columns at a time based on query
	* Note3:Before query execution load marks table and calculate the avg and cgpa
	       
      * table name: student
      
	  * Columns available:
					rollno,
					name,
					exam1,
					exam2,
					exam3,
					exam4,
					avg,
					cgpa
          
      * For all: *
      * options are:
      
            gt : greater than
                select * from student where exam1 gt 50
            eq : equal
                select * from student where rollno eq 8
            lt : less than
                select * from student where exam3 lt 50
            ge : greater than or qual to
                select * from student where exam4 ge 50
            le : less than or equal to
                select * from student where avg le 50
            contains : contains name
                select * from student where name contains ll
            startswith : name startstih 
                select * from student where name startswith G
      * Insteas of star we can use any columns name like name, rollno etc
