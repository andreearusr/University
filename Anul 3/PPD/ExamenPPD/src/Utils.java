import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Utils {

    public static void fisGenerator() {

        List list = new ArrayList();
        list.add(1);
        list.add(2);
        list.add(3);
        list.add(4);

        for(int j=0; j<5; j++) {
            try {
//                int id = 1;
                File file = new File("./input/" + (j + 1) + ".txt");
                file.createNewFile();
                FileOutputStream fos = new FileOutputStream(file);
                BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));

                for (int i = 0; i < 50; i++) {
                    Random rand = new Random();
                    int nr = rand.nextInt(4) + 1;
                    int id = rand.nextInt(50) + 1;
                    bw.write(id + "," + nr);
                    bw.newLine();
//                    id++;
                }
                bw.close();
                fos.close();
            }catch (IOException e) {
                e.printStackTrace();
            }
        }


    }

}


