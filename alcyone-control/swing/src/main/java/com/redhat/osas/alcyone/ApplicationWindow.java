package com.redhat.osas.alcyone;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.InputEvent;
import java.awt.CardLayout;
import javax.swing.JSeparator;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import javax.swing.JButton;
import java.awt.GridLayout;
import java.awt.FlowLayout;
import java.io.IOException;

public class ApplicationWindow {

	private JFrame frmAlcyoneController;
	private JTextField txtOctave;
	private JTextField txtTransposition;
	private JTextField txtChannel;

	String alcyoneHost = "piui";
	String alcyonePort = "8090";
	AlcyoneConnection connection = new AlcyoneConnection("192.168.1.108", 8090);

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
	 * Create the application.
	 */
	public ApplicationWindow() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frmAlcyoneController = new JFrame();
		frmAlcyoneController.setTitle("Alcyone Controller");
		frmAlcyoneController.setBounds(100, 100, 454, 177);
		frmAlcyoneController.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
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
		panelControl.add(btnTranspositionUp);

		JButton btnChannelUp = new JButton("Channel Up");
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
		panelControl.add(btnTransposeDown);

		JButton btnChannelDown = new JButton("Channel Down");
		panelControl.add(btnChannelDown);
		updateStatus(panelControl);
	}

	private void updateStatus(JPanel panelControl) {
		try {
			AlcyoneStatus s = connection.getStatus();
			txtOctave.setText(Integer.toString(s.getOctave()));
			txtChannel.setText(Integer.toString(s.getChannel()));
			txtTransposition.setText(Integer.toString(s.getTransposition()));
			panelControl.invalidate();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

}
