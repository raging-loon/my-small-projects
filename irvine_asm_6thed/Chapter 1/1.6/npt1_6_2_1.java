/*
 * Write a Java program that contains the following calculation. Then, use the javap –c command to disassemble your code. Then, add comments to each line that provide your best
  guess as to its purpose.
    int Y; // I set this to five
    int X = (Y + 4) * 3;
 * 
 * 
 */


public class npt1_6_2_1{

  public static void main(String [] args){
    int Y = 5;
    int X = (Y + 4) * 3;
  }
}

/*
Compiled from "npt1_6_2_1.java"
public class npt1_6_2_1 {
  public npt1_6_2_1();
    Code:
       0: aload_0
       1: invokespecial #1                  // Method java/lang/Object."<init>":()V
       4: return

  public static void main(java.lang.String[]);
    Code:
       0: iconst_5  // put 5 in a register
       1: istore_1  // put the above into a memory location
       2: iload_1   // load Y
       3: iconst_4  // put 4 in a register
       4: iadd      // add 4 and Y
       5: iconst_3  // move 3 into a register
       6: imul      // multiply by another register
       7: istore_2  // store it in X
       8: return
}

 */