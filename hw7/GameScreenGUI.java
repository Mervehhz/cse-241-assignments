import java.awt.Color;
import java.awt.EventQueue;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;

public class GameScreenGUI implements Cloneable{

	private JFrame frmHex;
	
	public int boardSize;
	
	String gameMode;
	
	public int turn = 0;	
	
	int[][] arrPink;
	int[][] arrBlue;
	
	public List<ArrayList<String>> arrList = new ArrayList<>(); 
	public List<JButton> buttons = new ArrayList<>();
	
	public GameScreenGUI(int boardSize, String gameMode) {
		this.gameMode = gameMode;
		this.boardSize = boardSize;	
		arrPink = new int[boardSize][boardSize];
		arrBlue = new int[boardSize][boardSize];
		initialize();
		
		
	}

	private void initialize() {
		frmHex = new JFrame();
		frmHex.setTitle("Hex");
		frmHex.setBounds(100, 100, 450, 300);
		frmHex.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frmHex.getContentPane().setLayout(new GridLayout(this.boardSize + 2 , this.boardSize + 2));
		frmHex.setVisible(true);
		
		int multipleOfBoardSize = 0;
		int row = 0;
		
		for (int i = 0; i < boardSize; i++) {
			arrList.add(new ArrayList<>());
		}
		for (int p = 0; p < arrList.size(); p++) {
			for (int j = 0; j < boardSize; j++) {
				arrList.get(p).add("white");
			}
		}
		
		for (int i = 0; i < (boardSize +2) * (boardSize+2); i++) {
			boolean isWon = false;
			int rowTemp = row;
			int multipleTemp = multipleOfBoardSize;
			if ( i == 0) {
				JButton b = new JButton();
				b.setBackground(Color.WHITE);
				b.setEnabled(false);
				frmHex.getContentPane().add(b);
				continue;
			}
			
			if (i == boardSize + 1) {
				JButton b = new JButton("Reset Game");
				b.setBackground(new Color(204, 255, 51));
				b.addActionListener(new ActionListener() {
					
					@Override
					public void actionPerformed(ActionEvent e) {
						frmHex.setVisible(false);
						frmHex.dispose();
						MainMenuGUI mainMenuGUI = new MainMenuGUI();
						
						
					}
				});
				frmHex.getContentPane().add(b);
				continue;
			}
			
			if (i == (boardSize +2) * (boardSize+2) - 1) {
				JButton b = new JButton("Undo");
				b.setBackground(new Color(204, 255, 51));
				
				b.addActionListener(new ActionListener() {
					
					@Override
					public void actionPerformed(ActionEvent e) {
						GameScreenGUI gameScreenGUi;					
					}
				});
				
				frmHex.getContentPane().add(b);
				continue;
			}
			
			if (i == ((boardSize + 2) * (boardSize + 2)) - boardSize - 2) {
				JButton b = new JButton();
				b.setBackground(Color.WHITE);
				b.setEnabled(true);
				b.addActionListener(new ActionListener() {
					
					@Override
					public void actionPerformed(ActionEvent e) {
						for (int i = 0; i < arrList.size(); i++) {
							for (int j = 0; j < boardSize; j++) {
								System.out.println(arrList.get(i).get(j));
							}
						}
						
					}
				});
				frmHex.getContentPane().add(b);
				continue;
			}
			if (i <= boardSize || (i > (boardSize + 2) * (boardSize + 1) && i < (boardSize +2) * (boardSize+2) - 1 )) {
				JButton b = new JButton();
				b.setBackground(Color.CYAN);
				frmHex.getContentPane().add(b);
				b.setEnabled(false);
				continue;
			} 
			if (isRed(i)) {
				JButton b = new JButton();
				b.setBackground(Color.PINK);
				frmHex.getContentPane().add(b);
				b.setEnabled(false);
				continue;
			}
			
			JButton b = new JButton();
			b.setBackground(Color.WHITE);
			b.addActionListener(new ActionListener() {
				
				@Override
				public void actionPerformed(ActionEvent e) {					/*       here           */
		
					if (turn % 2 == 0) {
						
						arrList.get(rowTemp).set(multipleTemp,"pink");
						
						b.setBackground(Color.PINK);
						turn++;
						
						arrPink[rowTemp][multipleTemp] = 1;
						
						for (int i = 0; i < boardSize; i++) {
							
							if (arrPink[i][0] == 1 && isGameOver(i, 0,arrPink)) {
								JOptionPane.showMessageDialog(frmHex, "Pink Won");
								System.exit(0);
							}
							
						}
					
					} else {
						arrList.get(rowTemp).set(multipleTemp,"blue");
						b.setBackground(Color.CYAN);
						turn++;
						arrBlue[multipleTemp][rowTemp] = 1;
						
						for (int i = 0; i < boardSize; i++) {
							
							if (arrBlue[i][0] == 1 && isGameOver(i, 0,arrBlue)) {
								JOptionPane.showMessageDialog(frmHex, "Blue Won");
								System.exit(0);
							}
							
						}
					}
					checkedList.clear();
					b.setEnabled(false);
					
					if (turn == boardSize*boardSize) {
						JOptionPane.showMessageDialog(frmHex, "Draw");
						System.exit(0);
					}
					
				}
			});
			multipleOfBoardSize++;
			if (multipleOfBoardSize % boardSize == 0) {
				multipleOfBoardSize = multipleOfBoardSize % boardSize;
				row++;
			}
			buttons.add(b);
			frmHex.getContentPane().add(b);	
			
		}
	
		frmHex.setVisible(true);
		
		playGame();
		
	}

	public boolean isRed(int val) {
		
		for (int i = 1; i < boardSize + 1; i++) {
			int n = i * (boardSize + 2);
			if (n ==  val) return true;
			if (n + boardSize +1 == val) return true;
		}
		
		return false;
	}
	
	public void playGame() {
		
		if (this.gameMode.equals("Computer vs User")) {
			
		}	
	}
	
	
	public boolean isGameOver(int row, int column, int[][] arr) {
		if (column == boardSize - 1) return true;
		
		int[][] tempArr = arr;
		tempArr[row][column] = 0;
		if (tempArr[row][column + 1] == 1 && isGameOver(row, column + 1,tempArr) ) {
			return true; //sağ
		}
		
		if (row < boardSize -1  && column < boardSize - 1 &&  tempArr[row + 1][column + 1] == 1 && isGameOver(row + 1, column + 1,tempArr) ) {
			return true; //sağ alt
		}
				
		if (row >= 1 && tempArr[row - 1][column + 1] == 1 && isGameOver(row - 1, column + 1,tempArr) ) {
			return true; //sağ üst
		}
		
		if (row >= 1 && tempArr[row + 1][column] == 1 && isGameOver(row + 1, column,tempArr) ) {
			return true; //alt
		}
		
		if (row >= 1 && tempArr[row - 1][column] == 1 && isGameOver(row - 1, column,tempArr) ) {
			return true; //üst
		}
		
		if (row >= 1 && column >= 1 && tempArr[row - 1][column - 1] == 1 && isGameOver(row - 1, column,tempArr) ) {
			return true; // sol üst
		}
		if (column >= 1 && tempArr[row + 1][column - 1] == 1 && isGameOver(row + 1, column - 1, tempArr) ) {
			return true; // sol alt
		}
		if (column >= 1 && tempArr[row][column - 1] == 1 && isGameOver(row, column - 1,tempArr) ) {
			return true; // sol
		}
		//this.checkedList.add(b);
		tempArr[row][column] = 1;
		//map.put(row,column);
		return false;
	}

}
