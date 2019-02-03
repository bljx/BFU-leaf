/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package fileSystem;

import java.io.File;
import javax.swing.filechooser.FileFilter;

/**
 *
 * @author jiangnan
 */
public class fileFilter extends FileFilter {

    String ext;

    public fileFilter(String ext) {
        this.ext = ext;
    }

    @Override
    public boolean accept(File file) {
        String name = file.getName().toLowerCase();
        if (name.endsWith(ext) || file.isDirectory()) {
            return true;
        } else {
            return false;
        }
    }

    @Override
    public String getDescription() {
        if (ext.equals("pl0")) {
            return "*.pl0";
        } else if (ext.equals("txt")) {
            return "*.txt";
        }
        return "";
    }
}
