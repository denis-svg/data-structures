import problems.Infix;
public class Main {

    public static void main(String[] args){
        long start = System.nanoTime();
        System.out.print(Infix.infixCalc("(21 - 14)(21 + 14)^0.5"));
        System.out.println(" : " + (System.nanoTime() - start)/1000 + " microseconds");
        start = System.nanoTime();
        System.out.print(Infix.infixCalc("1 + 2 * (20 / 5 )^3 - 434.44 / 21321 + 12"));
        System.out.println(" : " + (System.nanoTime() - start)/1000 + " microseconds");
    }
}
