package compiler;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Arrays;

public class Scanner {

    public int lineCnt=0;
    private char curCh = ' ';
    private String line;
    public int lineLength = 0;
    public int chCount = 0;
    private int[] ssym;
    private BufferedReader in;

    public Scanner(String filePath) {
        try {
            in = new BufferedReader(new FileReader(filePath));
        } catch (FileNotFoundException ex) {
            ex.printStackTrace();
            System.out.println("***File not exist!***");
        }
        //设置单字符
        ssym = new int[256];
        Arrays.fill(ssym, Symbol.nul);
        ssym['+'] = Symbol.plus;
        ssym['-'] = Symbol.minus;
        ssym['*'] = Symbol.mul;
        ssym['/'] = Symbol.div;
        ssym['('] = Symbol.lparen;
        ssym[')'] = Symbol.rparen;
        ssym['='] = Symbol.eql;
        ssym[','] = Symbol.comma;
        ssym['.'] = Symbol.peroid;
        ssym[';'] = Symbol.semicolon;

    }

    //读取一个字符，为减少磁盘I/O次数，每次读取一行
    void getch() {
        if (chCount == lineLength) {
            try {//如果读到行末尾，就重新读入一行
                String tmp="";
                while (tmp.equals("")) {
                    tmp=in.readLine().trim()+' ';               //除去空行
                }
                line=tmp;
                lineCnt++;
            } catch (Exception e) {
                // throw new Error("***program imcomplete!***");
                e.printStackTrace();
                System.out.println("***reading character meet with error!***");
            }
            lineLength = line.length();
            chCount = 0;
            System.out.println(line);
        }
        curCh = line.charAt(chCount++);
    }

    //词法分析，获取一个词法分析符号，是词法分析器的重点
    public Symbol getsym() {
        Symbol sym;
        while (curCh == ' ') {
            getch();
        }
        if ((curCh >= 'a' && curCh <= 'z')||(curCh >= 'A' && curCh <= 'Z')) {
            sym = matchKeywordOrIdentifier();                                     //关键字或者一般标识符
        } else if (curCh >= '0' && curCh <= '9') {
            sym = matchNumber();                                                       //数字
        } else {
            sym = matchOperator();                                                     //操作符
        }
        return sym;
    }

    private Symbol matchKeywordOrIdentifier() {
        StringBuffer sb = new StringBuffer();
        do{
            sb.append(curCh);
            getch();
        }while((curCh >= 'a' && curCh <= 'z')||(curCh>='A'&&curCh<='Z') || (curCh >= '0' && curCh <= '9'));

        String token = sb.toString();
        int index = Arrays.binarySearch(Symbol.word, token);                           //搜索是不是保留字
        Symbol sym = null;
        if (index < 0) {
            sym = new Symbol(Symbol.ident);                                            //一般标识符
            sym.id = token;
        } else {
            sym = new Symbol(Symbol.wsym[index]);                                    //保留字对应的符号值0-31
        }
        return sym;
    }

    private Symbol matchNumber() {
        //统计数字位数
        Symbol sym = new Symbol(Symbol.number);
        do {                      
            sym.num = 10 * sym.num + curCh - '0';                                    // 获取数字的值
            getch();
        } while (curCh >= '0' && curCh <= '9');                                    //!!!

        return sym;
    }

    private Symbol matchOperator() {
        Symbol sym = null;
        switch (curCh) {
            case ':':                                                                       // 赋值符号
                getch();
                if (curCh == '=') {
                    sym = new Symbol(Symbol.becomes);
                    getch();
                } else {
                    sym = new Symbol(Symbol.nul);                               //不能识别的符号
                }
                break;
            case '<':                                                                    //小于或者小于等于
                getch();
                if (curCh == '=') {
                    sym = new Symbol(Symbol.leq);                             //是<=
                    getch();
                } else if (curCh == '>') {
                    sym = new Symbol(Symbol.neq);                           //是<>
                    getch();
                } else {
                    sym = new Symbol(Symbol.lss);                             //是<
                }
                break;
            case '>':                                                      //大于或者大于等于
                getch();
                if (curCh == '=') {
                    sym = new Symbol(Symbol.geq);                           //大于等于
                    getch();
                } else {
                    sym = new Symbol(Symbol.gtr);                            //大于
                }
                break;
            default:
                sym = new Symbol(ssym[curCh]);
                if (sym.symtype != Symbol.peroid) {
                    getch();
                }
        }
        return sym;
    }
}
