package problems;
import java.util.ArrayList;
import java.util.Hashtable;

import datastructure.Stack;

public class Infix {
    private static ArrayList<String> split(String infix_expression){
        ArrayList<String> infix_tokens = new ArrayList<>();
        String digits = "0123456789";
        String operands = "-+*/^";
        StringBuilder number = new StringBuilder();
        char previous = ' ';
        for (int i = 0;i < infix_expression.length();i++){
            if (digits.indexOf(infix_expression.charAt(i)) != -1 || infix_expression.charAt(i) == '.'){
                number.append(infix_expression.charAt(i));
                if (i + 1 == infix_expression.length()){
                    infix_tokens.add(number.toString());
                    break;
                }else if (previous == ')'){
                    infix_tokens.add("*");
                }
                previous = infix_expression.charAt(i);
            }else if (operands.indexOf(infix_expression.charAt(i)) != -1){
                if (digits.indexOf(previous) != -1){
                    infix_tokens.add(number.toString());
                    number.delete(0, number.length());
                }
                infix_tokens.add(String.valueOf(infix_expression.charAt(i)));
                previous = infix_expression.charAt(i);
            }else if (infix_expression.charAt(i) == '('){
                if (digits.indexOf(previous) != -1) {
                    infix_tokens.add(number.toString());
                    number.delete(0, number.length());
                    infix_tokens.add("*");
                }else if (previous == ')'){
                    infix_tokens.add("*");
                }
                infix_tokens.add(String.valueOf(infix_expression.charAt(i)));
                previous = infix_expression.charAt(i);
            }else if (infix_expression.charAt(i) == ')'){
                if (digits.indexOf(previous) != -1){
                    infix_tokens.add(number.toString());
                    number.delete(0, number.length());
                }
                infix_tokens.add(String.valueOf(infix_expression.charAt(i)));
                previous = infix_expression.charAt(i);
            }
        }
        return infix_tokens;
    }
    private static ArrayList<String> infixToPostfix(ArrayList<String> infix_tokens){
        ArrayList<String> postfix_tokens = new ArrayList<String>();
        Stack<Character> op_stack = new Stack<Character>();
        Hashtable<Character, Integer> prec = new Hashtable<Character, Integer>();
        String digits = "0123456789";
        prec.put('^', 4);
        prec.put('*', 3);
        prec.put('/', 3);
        prec.put('-', 2);
        prec.put('+', 2);
        prec.put('(', 1);
        for (String token : infix_tokens){
            if (digits.indexOf(token.charAt(0)) != -1){
                postfix_tokens.add(token);
            }else if (token.charAt(0) == '('){
                op_stack.push(token.charAt(0));
            }else if (token.charAt(0) == ')'){
                Character top_operand = op_stack.pop();
                while (top_operand != '('){
                    postfix_tokens.add(top_operand.toString());
                    top_operand = op_stack.pop();
                }
            }else{
                while (!op_stack.isEmpty()){
                    if (prec.get(token.charAt(0)) <= prec.get(op_stack.peek())){
                        postfix_tokens.add(op_stack.pop().toString());
                    }else{
                        break;
                    }
                }
                op_stack.push(token.charAt(0));
            }
        }
        while (!op_stack.isEmpty()){
            postfix_tokens.add(op_stack.pop().toString());
        }
        return postfix_tokens;
    }
    private static double do_math(Double operator2, Double operator1, Character operator){
        return switch (operator) {
            case '+' -> operator1 + operator2;
            case '-' -> operator1 - operator2;
            case '*' -> operator1 * operator2;
            case '/' -> operator1 / operator2;
            case '^' -> Math.pow(operator1, operator2);
            default -> throw new IllegalArgumentException(operator + "unknown operator");
        };
    }
    private static double postfixCalc(ArrayList<String> postfix_tokens){
        Stack<Double> operator_stack = new Stack<Double>();
        String digits = "0123456789";
        for(String token : postfix_tokens){
            if (digits.indexOf(token.charAt(0)) != -1){
                operator_stack.push(Double.parseDouble(token));
            }else{
                operator_stack.push(do_math(operator_stack.pop(), operator_stack.pop(), token.charAt(0)));
            }
        }
        return operator_stack.pop();
    }
    public static double infixCalc(String infix_expression){
        ArrayList<String> infix_tokens = Infix.split(infix_expression);
        ArrayList<String> postfix_tokens = Infix.infixToPostfix(infix_tokens);
        return Infix.postfixCalc(postfix_tokens);
    }
}
