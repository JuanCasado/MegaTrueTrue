/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicBoolean;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;

/**
 *
 * @author mr.blissfulgrin
 */
public class Bluetooth extends Thread implements Clickable{
    private OutputStream outStream;
    private PrintWriter pWriter = null;
    private InputStream inStream = null;
    private BufferedReader bReader2 = null;
    private BufferedReader bReader;
    private StreamConnection streamConnection;
    private final String url;
    private final AtomicBoolean control;
    private final ConcurrentHashMap <String,Holder> holders;
    private final HUD hud;
    
    public Bluetooth (){
        this.url = "btspp://98D33211113B:1;authenticate=false;encrypt=false;master=false";
        control = new AtomicBoolean(false);
        holders = new ConcurrentHashMap <>();
        hud = new HUD(this);
    }
    private void createConnection ()throws Exception{
        streamConnection = (StreamConnection) Connector.open(url);
        outStream = streamConnection.openOutputStream();
        pWriter = new PrintWriter(new OutputStreamWriter(outStream));
        inStream = streamConnection.openInputStream();
        bReader2 = new BufferedReader(new InputStreamReader(inStream));
        bReader = new BufferedReader(new InputStreamReader(System.in));
    }
    public synchronized void send (String data){
        if (control.get()){
            pWriter.write(data);
            pWriter.flush();
        }
    }
    @Override
    public void run (){
        try{
            try{
                createConnection();
                control.set(true);
                System.out.println("CONNECTED");
            }catch (Exception e){
                control.set(false);
                System.out.println("NOT CONNECTED");
            } 
            String splitData [];
            String str;
            Scenes.clear();
            Scenes.add(hud);
            while (control.get()){
                if(inStream.available() > 0){
                    str = bReader2.readLine();
                    if (str != null){
                        System.out.println(str);
                        splitData = str.split(" ");
                        switch (splitData[0]){
                            case "M": 
                                holders.forEachValue(NORM_PRIORITY, (holder)->{
                                    holder.end();
                                });
                                holders.clear();
                                if (splitData.length>1)
                                    hud.setTextMenu(splitData[1].replace("_", " "));
                                if (splitData.length>2){
                                    switch (splitData[2]){
                                        case "1":
                                            holders.put("1",new Holder(Holder.MODO.FULL,this));
                                            break;
                                        case "2":
                                            holders.put("1",new Holder(Holder.MODO.HD,this));
                                            holders.put("2",new Holder(Holder.MODO.HI,this));
                                            break;
                                        case "3":
                                            holders.put("1",new Holder(Holder.MODO.HI,this));
                                            holders.put("2",new Holder(Holder.MODO.Q2,this));
                                            holders.put("3",new Holder(Holder.MODO.Q4,this));
                                            break;
                                        case "4":
                                            holders.put("1",new Holder(Holder.MODO.Q1,this));
                                            holders.put("2",new Holder(Holder.MODO.Q2,this));
                                            holders.put("3",new Holder(Holder.MODO.Q3,this));
                                            holders.put("4",new Holder(Holder.MODO.Q4,this));
                                            break;
                                    }
                                    holders.values().forEach((holder)->{
                                        Scenes.add(holder);
                                    });
                                }
                                break;
                            case "1":
                                if (holders.containsKey("1"));
                                    procesarHolder(splitData);
                                break;
                            case "2":
                                if (holders.containsKey("2"));
                                    procesarHolder(splitData);
                                break;
                            case "3":
                                if (holders.containsKey("3"));
                                    procesarHolder(splitData);
                                break;
                            case "4":
                                if (holders.containsKey("4"));
                                    procesarHolder(splitData);
                                break;
                        }
                    }
                }
            }
        }catch(IOException e){control.set(false);}
    }
    private void procesarHolder(String [] splitData){
        if (splitData.length>1)
            switch (splitData[1]){
                case "B":
                    if (splitData.length>2)
                        holders.get(splitData[0]).setTipo(Holder.TIPO.Botonera,Integer.valueOf(splitData[2]));
                    break;
                case "C":
                    holders.get(splitData[0]).setTipo(Holder.TIPO.Colector,0);
                    break;
                case "G":
                    holders.get(splitData[0]).setTipo(Holder.TIPO.Grafica,0);
                    break;
                case "D":
                    holders.get(splitData[0]).setTipo(Holder.TIPO.Display,0);
                    break;
                default:
                    if (splitData.length>2)
                        holders.get(splitData[0]).add(splitData[1],splitData[2]);
                    break;
            }
    }
    public void close (){
        control.set(false);
        try {
            streamConnection.close();
        } catch (IOException | NullPointerException ex) {}
        try {
            outStream.close();
        } catch (IOException | NullPointerException ex) {}
        try {
            pWriter.close();
        } catch (NullPointerException ex) {}
        try {
            inStream.close();
        } catch (IOException | NullPointerException ex) {}
        try {
            bReader2.close();
        } catch (IOException | NullPointerException ex) {}
        try {
            bReader.close();
        } catch (IOException | NullPointerException ex) {}
    }
    public boolean isConnected(){
        return control.get();
    }

    @Override
    public void click(float x, float y) {
        holders.forEachValue(NORM_PRIORITY, (holder)->{
            holder.click(x, y);
        });
    }

    @Override
    public void release(float x, float y) {
        holders.forEachValue(NORM_PRIORITY, (holder)->{
            holder.release(x, y);
        });
    }
}
