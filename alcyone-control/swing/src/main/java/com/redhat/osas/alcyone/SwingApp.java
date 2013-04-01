package com.redhat.osas.alcyone;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * User: jottinge
 * Date: 4/1/13
 * Time: 11:21 AM
 */
public class SwingApp {
    public static void main(String[] args) {
        new SwingApp().buildAndRunGui();
    }

    private void buildAndRunGui() {
        JFrame alcyoneController=new JFrame("Alcyone Controller");
        alcyoneController.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        alcyoneController.setLayout(new BorderLayout());

        JMenuBar menuBar=new JMenuBar();
        JMenu jMenu=new JMenu("File");
        menuBar.add(jMenu);
        JMenuItem menuItem=new JMenuItem("Exit");
        menuItem.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
        jMenu.add(menuItem);
        menuItem=new JMenuItem("Configure");


        alcyoneController.setJMenuBar(menuBar);
        alcyoneController.pack();
        alcyoneController.setVisible(true);

    }
}
