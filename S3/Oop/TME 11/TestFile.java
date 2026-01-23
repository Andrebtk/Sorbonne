import java.io.File;
import java.io.IOException;

public class TestFile {

	public static void pwd() {
		File f = new File("");
		System.out.println(f.getAbsolutePath());
	}
	
	public static String ls(File f) {
			String res = "";
			File[] lst = f.listFiles();
			
			/*for(int i=0; i<lst.length; i++){
				res += lst[i].toString()+"\n";
			}*/
			
			return res;
	}

	public static void main(String[] args){
		try{
			File f = new File(args[0]);
			pwd();
			ls(new File(""));
			
			f.delete();
			System.out.println("le fichier existe : " + (f.exists() ? "oui": "non"));
			f.createNewFile();
			System.out.println("le fichier existe : " + (f.exists()?"oui":"non"));
			System.out.println(f.getAbsolutePath());
			
		}catch(IOException e){
			System.out.println(e);
		}
	}
}
