/* Julius Ahenkora
 * 
 */

import java.io.*;
import java.util.Scanner;


/**
 *  A class to check 3x3 KenKen puzzles stored in a
 *  weird file format.
 */
class KenKenChecker {
 /**
  *  The size of the KenKen puzzles
  */
 public static final int SIZE = 3;
 
 public String puzzleString="";
 
 
 /**
  *  This constructor opens the file and stores
  *  the puzzle and associated cages. Assumes
  *  the file has a valid format.
  *  
  *  @param the name of the file to check
  */
 public KenKenChecker(String file) throws FileNotFoundException {
   
   Scanner input = new Scanner (new File(file));
   
   while(input.hasNextLine()) {
     puzzleString += input.nextLine();
     puzzleString += "\n";
     }
   
   input.close();
 }
 
 
 
 /**
  *  Returns the puzzle, where location (0,0) is the top left,
  *  (0,1) is the top middle, and (2,2) is the bottom right.
  *  
  *  @return the puzzle
  */
 public int[][] getPuzzle() {
  int puzzleInt;
  Scanner getPuzz = new Scanner(puzzleString);
  int[][] kenKenPuzzle = new int[SIZE][SIZE];
  for (int x = SIZE-1; x >= 0; x--) {
   for (int z = SIZE-1; z >= 0; z--) {
   puzzleInt = getPuzz.nextInt();
  
   kenKenPuzzle[x][z] = puzzleInt; 
  }}
 return kenKenPuzzle;
 }
 
 /*Gets the original, unsorted puzzle
  * 
  * 
  * @return Original, unsorted puzzle
  */
 
 public int[][] getOldPuzzle() {
  int puzzleInt;
  Scanner getPuzz = new Scanner(puzzleString);
  int[][] kenKenPuzzle = new int[SIZE][SIZE];
  for (int x = 0; x < SIZE; x++) {
   for (int z = 0; z < SIZE; z++) {
   puzzleInt = getPuzz.nextInt();
  
   kenKenPuzzle[x][z] = puzzleInt; 
  }}
 return kenKenPuzzle;
 }
 
 /*Gets max number of cages in puzzle
  * 
  * @return Max number of cages in puzzle
  */
 public int getCageSize() {
   Scanner getCage = new Scanner(puzzleString);
   int maxCages = 0;
   while(getCage.hasNextInt()) {
    getCage.nextInt();
    
  }
  getCage.next();
  maxCages = getCage.nextInt();
 
  return maxCages;
 }
 
 /*Gets an array of puzzle operations
  * 
  * @return An array of cage operations
  */
 public String[] numOperations() {
  Scanner getCage = new Scanner(puzzleString);
  int x = 0;
  int maxCages = getCageSize();
  
  String[] numOperationsArr = new String[maxCages];
  
  while(getCage.hasNext()) {
    
   String currentVal = "";
   currentVal = getCage.next();
   
   if ((currentVal.equals("+") || currentVal.equals("-") || currentVal.equals("x"))){
     numOperationsArr[x] = currentVal;
     x++;
  }}
  
  return numOperationsArr;
  }
  
 /*Creates an array of results from puzzle
  * 
  * @return Array of cage results
  */
 
 public int[] resultOperation() {
   Scanner getCage = new Scanner(puzzleString);
   int maxCages = getCageSize();
   int[] resOperationsArr = new int[maxCages];
   int x = 0;
   
   while(getCage.hasNext()) {
    String currentVal = "";
    currentVal = getCage.next();
  
   if ((currentVal.equals("+") || currentVal.equals("-") || currentVal.equals("x"))){
     currentVal = getCage.next();
     resOperationsArr[x] = Integer.parseInt(currentVal);
     x++;
  }}
   
 return resOperationsArr;
 }
 
 //@return Returns an array of the max number of locations in each operation.
 public int[] getNumLocations() {
 
 int maxCages = getCageSize();
 Scanner getCage = new Scanner(puzzleString);
 int[] numLocationArr = new int[maxCages];
 int x = 0;
 
 while(getCage.hasNext()) {
    
   String currentVal = "";
   currentVal = getCage.next();
   
   if ((currentVal.equals("+") || currentVal.equals("-") || currentVal.equals("x"))){
    currentVal = getCage.next();
    currentVal = getCage.next();
    numLocationArr[x] = Integer.parseInt(currentVal);
    x++;
  }}
 
  return numLocationArr;
 }
  
  
 
 
 
 
 /**
  *  Returns an array of all the cages (accessor).
  *  
  *  @return all the cages
  * 
  */
 
 public String[] getCageArray() {
 
  Scanner getCage = new Scanner(puzzleString);
  int maxCages = getCageSize();
  
  String[] cageArray = new String[maxCages];
  int[] getNumLocations = getNumLocations();
  String currentVal = "";
  int x = 0;
  
  while(getCage.hasNextLine() && x < maxCages) {
    int z = 0;
    currentVal = getCage.next();
      if ((currentVal.equals("+") || currentVal.equals("-") || currentVal.equals("x"))){
        while(getNumLocations[x] >= z) {
          if (z==0){
            cageArray[x] =  currentVal + getCage.nextLine();
            z++;
            }
          else{
          
            cageArray[x] +=  " "+ getCage.nextLine();
            z++;
            }
          }
          x++;
        }
     }return cageArray;}
 
 
 
 /*Acquires an array of cage operation, location, and result for each cage in puzzle.
  * 
  * 
  * @return Returns an array of cages.
  */
 public Cage[] getCages() {
  
  int maxCages = getCageSize();
  Cage[] kenKenCage = new Cage[maxCages];
  String[] cageArray = getCageArray();
  int[] numOperationsArr = resultOperation();
  int[] numLocationArr = getNumLocations();
  String[] operationType = numOperations();
  int numLocation;
  int maxCoordinates = 2 ;
  
  for(int x = 0; x < maxCages; x++) {
    numLocation = numLocationArr[x];
    Scanner getCage = new Scanner(cageArray[x]);
    getCage.next();
    getCage.next();
    getCage.next();
    int[][] getArrayz = new int [numLocation][maxCoordinates];
    
    for(int k = 0; k < numLocation; k++) {
     for (int z = 0; z < maxCoordinates; z++) {
       getArrayz[k][z] = getCage.nextInt();
       }}
     kenKenCage[x] = new Cage(numLocationArr[x], numOperationsArr[x],operationType[x],getArrayz);
     }
    return kenKenCage;
   } 
   
   
/**
  *  Returns whether or not the puzzle is valid
  *  given the solution and the cages of the puzzle.
  *  
  *  @return whether or not the puzzle is valid
  */
 public boolean isValid() {
   
   boolean getSolution = false;
   int[][] puzzleSolution = getOldPuzzle();
   Cage[] kenkenCheck = getCages();
   int maxCageSize = getCageSize();
   int totalResultant = 0;
   int[] arrayLocation;
   int opperand = 0;
   int currentResult = 0;
   int maxCoordinates = 2;
   int totalValid = 0;
   int k = 0;
   
   
   for(int x=0; x < maxCageSize; x++) {
    
       opperand = kenkenCheck[x].getOperation();
       totalResultant = kenkenCheck[x].getResult();
       currentResult = 0;
       
       for(int z = 0; z < kenkenCheck[x].getNumLocations(); z++){
         arrayLocation = kenkenCheck[x].getLocation(z);
         
         if (opperand == 0) {
           currentResult += puzzleSolution[arrayLocation[k+1]][arrayLocation[k]];
         }
         if(opperand == 1) {
           if(z == 0){
             currentResult = puzzleSolution[arrayLocation[k+1]][arrayLocation[k]];
           }
           else{
             currentResult -= puzzleSolution[arrayLocation[k+1]][arrayLocation[k]];
           }
        }
         if(opperand == 2) {
           if(z == 0) {
           
           currentResult = 1 * puzzleSolution[arrayLocation[k+1]][arrayLocation[k]];
           }
           else{
           currentResult *= puzzleSolution[arrayLocation[k+1]][arrayLocation[k]];
           }
         }
       }
       currentResult = Math.abs(currentResult);
       if (currentResult == totalResultant) {
         totalValid += 1;
        }
     }
    if (totalValid == maxCageSize) {
     getSolution = true;
   }
   
   return getSolution; 
     }

/**
  *  A main method to run your program.
  *  Do not change this.
  */
 public static void main(String[] args) {
   
  //get the puzzles directory
  File dir = new File("./puzzles");
  
  //check that the directory exists and is a real directory
  if(dir.exists() && dir.isDirectory()) {
   for(String fileName : dir.list()) {
    //append directory name so KenKenChecker can find the puzzle
    fileName = "./puzzles/" + fileName;
    
    //try to validate the KenKen puzzle, but produce an error if the file is invalid
    //without crashing the program
    try {
     KenKenChecker checker = new KenKenChecker(fileName);
     System.out.println("File: " + fileName);
     System.out.println("\t" + (checker.isValid() ? "Valid" : "Invalid"));
    }
    catch(FileNotFoundException e) {
     System.out.println("[File Error " + fileName + "]");
    }
   }
  }
 }
}
