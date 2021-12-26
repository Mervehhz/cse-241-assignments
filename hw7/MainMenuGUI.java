import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.SwingConstants;
import javax.swing.JTextField;
import javax.swing.AbstractButton;
import javax.swing.ButtonGroup;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.util.Enumeration;
import java.awt.event.ActionEvent;
import javax.swing.JLayeredPane;

public class MainMenuGUI {
	
	private JFrame frmHex;

	
	public MainMenuGUI() {
		initialize();
	}

	
	private void initialize() {
		ButtonGroup bg = new ButtonGroup();
		frmHex = new JFrame();
		frmHex.setTitle("Hex");
		frmHex.getContentPane().setBackground(new Color(204, 255, 51));
		frmHex.getContentPane().setForeground(new Color(0, 0, 0));
		frmHex.setBounds(100, 100, 450, 300);
		frmHex.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmHex.getContentPane().setLayout(null);
		
		JRadioButton humanVsHuman = new JRadioButton("Human vs Human");
		humanVsHuman.setFont(new Font("Tahoma", Font.BOLD, 11));
		humanVsHuman.setBackground(new Color(204, 255, 0));
		humanVsHuman.setForeground(new Color(0, 0, 0));
		humanVsHuman.setBounds(44, 44, 132, 23);
		frmHex.getContentPane().add(humanVsHuman);
		
		JRadioButton computerVsUser = new JRadioButton("Computer vs User");
		computerVsUser.setFont(new Font("Tahoma", Font.BOLD, 11));
		computerVsUser.setBackground(new Color(204, 255, 0));
		computerVsUser.setForeground(new Color(0, 0, 0));
		computerVsUser.setBounds(44, 90, 139, 23);
		frmHex.getContentPane().add(computerVsUser);
		
		JLabel instructions = new JLabel("Please choose game mode and board size.");
		instructions.setHorizontalAlignment(SwingConstants.LEFT);
		instructions.setFont(new Font("Tahoma", Font.PLAIN, 11));
		instructions.setBounds(44, 149, 224, 42);
		frmHex.getContentPane().add(instructions);
		
		JLabel boardSize = new JLabel("Board Size");
		boardSize.setFont(new Font("Tahoma", Font.BOLD, 11));
		boardSize.setBounds(237, 44, 85, 23);
		frmHex.getContentPane().add(boardSize);
		
		JComboBox comboBox = new JComboBox();
		comboBox.setModel(new DefaultComboBoxModel(new String[] {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"}));
		comboBox.setBounds(313, 44, 56, 22);
		frmHex.getContentPane().add(comboBox);
		//comboBox.add()
		
		bg.add(computerVsUser);
		bg.add(humanVsHuman);
		
		JButton playGame = new JButton("Start the Game");
		playGame.setBackground(Color.lightGray);
		playGame.setForeground(Color.BLACK);
		playGame.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				String s =  (String) comboBox.getSelectedItem();
				int boardSize = Integer.valueOf(s);
				String gameMode = gameMode(bg);
				if (gameMode == null) {
					throw new NullPointerException();
				}
				
				frmHex.setVisible(false);
				GameScreenGUI gameScreenGUI = new GameScreenGUI(boardSize, gameMode);
	
			}
		});
		playGame.setFont(new Font("Tahoma", Font.BOLD, 11));
		playGame.setBounds(248, 184, 139, 42);
		frmHex.getContentPane().add(playGame);
		frmHex.setVisible(true);
	}
	
	public String gameMode(ButtonGroup buttonGroup) {
		for (Enumeration<AbstractButton> buttons = buttonGroup.getElements(); buttons.hasMoreElements();) {
            AbstractButton button = buttons.nextElement();

            if (button.isSelected()) {
                return button.getText();
            }
        }
		return null;
	}
}
