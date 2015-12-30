All this code is in the package `assignment02`.

Make a class `Course`, which has as fields: a String `name` (e.g. "Programmming with Objects"), String `rubric` (e.g. "CS"), 
String `number` (e.g. "140" or "287C"), int `numCredits` (e.g. 4). All fields are private and you need to give a constructor that has 
4 parameters to set all the fields. There should be 4 getter methods.

Make a class `Offering`, with the special feature:

```java 
public class Offering implements Comparable<Offering> {
    ...
```

which has as fields: a Course `course`, an int `CRN` (e.g. 19732), an int `semester` (e.g. 201590), 201510 is winter, 
201520 is spring, 201560 is summer, 201590 is fall. All fields are private. Make a constructor that sets all the fields and getter methods for all the fields. 
As an explanation: a course can have a different CRN is different semesters. Add the _delegate_ method `public int getNumCredits()`, 
which returns `course.getNumCredits()`.

After all that code add the following methdod:

```java
   public int compareTo(Offering other) {
       if(other == null) return - 1;
       return semester - other.semester;
   }
```

Make a class `QPointsCalculator`, with a method:

```java
public static double points(String letterGrade, int credits)
```
which has a default return value of 0.0, returned at the end of the method and using if/else if/.../else if/else [see the textbook example of 
mutiple alternatives in Section 5.3]
changes that return value to 4.0*credits if letterGrade is "A", to 3.7*credits if letterGrade is "A-", to 3.3*credits if letterGrade is "B+", 
to 3.0*credits if letterGrade is "B", to 2.7*credits if letterGrade is "B-", to 2.3*credits if letterGrade is "C+", 
to 2.0*credits if letterGrade is "C", to 1.7*credits if letterGrade is "C-", to 1.0*credits if letterGrade is "D". In the final else part 
if lettergrade is not "P" or "F", then write the instruction:

```java
throw new IllegalArgumentException("Invalid Letter Grade");
```

Make a class `MyClass`, which has as fields: an Offering `course`, a double `qualityPoints`, an int `gpaCredits`, and a boolean `failed`. The constructor is different from
the previous ones. It takes `Offering cls` and `String letterGrd`. In the constructor, `course` is assigned to `cls`.
Set `gpaCredits` to `cls.getNumCredits()`. 
Set `qualityPoints` to `QPointsCalculator.points(letterGrd.toUpperCase(), gpaCredits)`. 
Now if `letterGrd.equalsIgnoreCase("P")`, set `gpaCredits` back to 0. 
If `letterGrd.equalsIgnoreCase("F")`, set `failed` to `true`
--the default value should be false (although you should check that).

Import assignment01.Person and make a class `Student` with fields Person `student` and an array `myClasses` of 50 `MyClass`.
Write a constuctor that only has a Person parameter. Write a method

```java
public int nextOpenClassIndex() {
// start at int val = 0 and while val < myClasses.length and myClasses[val] != null adds 1 to val
// return val.
}
```

Include the method 
```java
public void addToMyClass(MyClass mc) {
    int index = nextOpenClassIndex();
    myClasses[index] = mc;
}
```
Now we are going to compute your GPA based on the array myClasses. 

Version 1: Add up all the `getGpaCredits()` and all the `getQualityPoints()` of the Offering elements in `myClasses`. 
If the sum of all the gpa credits is 0 return 0, otherwise return the total quality points divided by the total gpa points.

Write a test class with a main method that creates a students with a record of several courses and show that the correct GPA is computed.
Here are some courses in the order: name, rubric, number, crn, credits, semester:

 * "Africa,Carib,Amer", "AFST","180R",12574,4,201190
 * "Calculus I", "MATH", "221", 11084, 4, 201190
 * "Coming to Voice", "WRIT", "111", 94123, 4, 201190
 * "Buried Cities & Lost Tribes", "ANTH", "125", 4, 201220
 * "Programming with Objects", "CS", "140", 10428, 4, 201220
 * "Calculus II", "MATH", "222", 11094, 4, 201220
 * "Intro Topics In Computer Scien", "CS", "101", 10039, 4, 201290
 * "Comp Sys I:Machine Org", "CS", "120", 22837, 4, 201290
 * "Pop, Rock, And Soul Musics", "MUS", "115", 10165, 4, 201290

TO DO Version 2 - still to come: make a clone of 'myClasses`, sort the clone and change 
repeated classes where the first attempt was not "F" to have 0 gpaCredits and 0 qualityPonts. Then do the GPA calculation