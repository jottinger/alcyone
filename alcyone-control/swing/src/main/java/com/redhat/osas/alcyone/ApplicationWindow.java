/*
    Copyright 2012- by Joseph B. Ottinger.

    This file is part of Alcyone.

    Alcyone is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Alcyone is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Alcyone.  If not, see <http://www.gnu.org/licenses/>.
*/

package com.redhat.osas.alcyone;

import com.redhat.osas.alcyone.impl.AlcyoneConnectionImpl;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;
import java.io.IOException;

public class ApplicationWindow {

    private final AlcyoneConnection connection = new AlcyoneConnectionImpl("192.168.1.108", 8090);
    private JFrame frmAlcyoneController;
    private JTextField txtOctave;
    private JTextField txtTransposition;
    private JTextField txtChannel;

    /**
     * Create the application.
     */
    private ApplicationWindow() {
        initialize();
    }

    /**
     * Launch the application.
     */
    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    ApplicationWindow window = new ApplicationWindow();
                    window.frmAlcyoneController.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }

    /**
     * Initialize the contents of the frame.
     */
    private void initialize() {
        frmAlcyoneController = new JFrame();
        frmAlcyoneController.setTitle("Alcyone Controller");
        frmAlcyoneController.setBounds(100, 100, 454, 177);
        frmAlcyoneController.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        JMenuBar menuBar = new JMenuBar();
        frmAlcyoneController.setJMenuBar(menuBar);

        JMenu mnNewMenu = new JMenu("File");
        mnNewMenu.setMnemonic('F');
        menuBar.add(mnNewMenu);

        JMenuItem mntmConfigure = new JMenuItem("Configure");
        mntmConfigure.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_C,
                InputEvent.ALT_MASK));
        mnNewMenu.add(mntmConfigure);

        JSeparator separator = new JSeparator();
        mnNewMenu.add(separator);

        JMenuItem mntmExit = new JMenuItem("Exit");
        mnNewMenu.add(mntmExit);
        mntmExit.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F4,
                InputEvent.ALT_MASK));
        mntmExit.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        FlowLayout flowLayout = new FlowLayout(FlowLayout.CENTER, 5, 5);
        frmAlcyoneController.getContentPane().setLayout(flowLayout);
        frmAlcyoneController.getContentPane().setLayout(
                new FlowLayout(FlowLayout.CENTER, 5, 5));

        final JPanel panelControl = new JPanel();
        frmAlcyoneController.getContentPane().add(panelControl);
        panelControl.setLayout(new GridLayout(3, 4, 0, 0));

        JButton btnOctaveUp = new JButton("Octave Up");
        btnOctaveUp.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    connection.changeOctave(AlcyoneVector.UP);
                } catch (IOException e1) {
                    // TODO Auto-generated catch block
                    e1.printStackTrace();
                }
                updateStatus(panelControl);
            }
        });
        panelControl.add(btnOctaveUp);

        JButton btnTranspositionUp = new JButton("Transpose Up");
        btnTranspositionUp.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    connection.changeTransposition(AlcyoneVector.UP);
                } catch (IOException e1) {
                    // TODO Auto-generated catch block
                    e1.printStackTrace();
                }
                updateStatus(panelControl);
            }
        });

        panelControl.add(btnTranspositionUp);

        JButton btnChannelUp = new JButton("Channel Up");
        btnChannelUp.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    connection.changeChannel(AlcyoneVector.UP);
                } catch (IOException e1) {
                    // TODO Auto-generated catch block
                    e1.printStackTrace();
                }
                updateStatus(panelControl);
            }
        });
        panelControl.add(btnChannelUp);

        txtOctave = new JTextField();
        panelControl.add(txtOctave);
        txtOctave.setColumns(10);

        txtTransposition = new JTextField();
        panelControl.add(txtTransposition);
        txtTransposition.setColumns(10);

        txtChannel = new JTextField();
        panelControl.add(txtChannel);
        txtChannel.setColumns(10);

        JButton btnOctaveDown = new JButton("Octave Down");
        btnOctaveDown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    connection.changeOctave(AlcyoneVector.DOWN);
                } catch (IOException e1) {
                    // TODO Auto-generated catch block
                    e1.printStackTrace();
                }
                updateStatus(panelControl);
            }
        });
        panelControl.add(btnOctaveDown);

        JButton btnTransposeDown = new JButton("Transpose Down");
        btnTransposeDown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    connection.changeTransposition(AlcyoneVector.DOWN);
                } catch (IOException e1) {
                    // TODO Auto-generated catch block
                    e1.printStackTrace();
                }
                updateStatus(panelControl);
            }
        });
        panelControl.add(btnTransposeDown);

        JButton btnChannelDown = new JButton("Channel Down");
        btnChannelDown.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    connection.changeChannel(AlcyoneVector.DOWN);
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
                updateStatus(panelControl);
            }
        });
        panelControl.add(btnChannelDown);
        updateStatus(panelControl);
    }

    private void updateStatus(JPanel panelControl) {
        AlcyoneStatus s = connection.getStatus();
        txtOctave.setText(Integer.toString(s.getOctave()));
        txtChannel.setText(Integer.toString(s.getChannel()));
        txtTransposition.setText(Integer.toString(s.getTransposition()));
        panelControl.invalidate();

    }

}
