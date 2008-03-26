/*
 * @(#)SIDV2librarian.java	beta1	2008/01/21
 *
 * Copyright (C) 2008    Rutger Vlek (rutgervlek@hotmail.com)
 *
 * This application is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this application; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

package org.midibox.sidedit.gui.bassline;

import java.awt.BorderLayout;
import java.awt.event.*;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import javax.swing.AbstractButton;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JToggleButton;

import org.midibox.sidedit.SIDEditController;
import org.midibox.sidedit.SIDSysexInfo;
import org.midibox.sidedit.SIDSysexParameterControl;
import org.midibox.utils.gui.ImageLoader;
import org.midibox.utils.gui.JVertLabel;
import org.midibox.utils.gui.Knob;
import org.midibox.utils.gui.MyButtonUI;
import  org.midibox.sidedit.gui.controls.*;
import org.midibox.sidedit.gui.lead.LeadGUI;

public class SequencerGUI extends JPanel implements ActionListener{
	private JPanel seqPanel,currentPanel,seq1,seq2,seq3,seq4,seq5,seq6,seq7,seq8;
	private JComboBox combo;
	private int[] snapvals = {0,1,2,3,4,5,6,7,8,9,10,11,12};
	
	protected SequencerGUI(Vector V1GUIv, Vector V2GUIv, Vector V3GUIv) {
		setLayout(new BorderLayout());
		this.setOpaque(false);
		
		JPanel mainPanel = new JPanel(); 
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.setOpaque(false);
		
		seqPanel = new JPanel();
		seqPanel.setLayout(new BoxLayout(seqPanel, BoxLayout.X_AXIS));
		seqPanel.setBorder(BorderFactory.createEtchedBorder());
		seqPanel.setBorder(BorderFactory.createTitledBorder("Sequencer data"));
		seqPanel.setOpaque(false);
		
		JPanel comboPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 0, 0));
		comboPanel.setOpaque(false);
		String[] s = {"Sequence #1","Sequence #2","Sequence #3","Sequence #4","Sequence #5","Sequence #6","Sequence #7","Sequence #8"};
		combo = new JComboBox(s);
		combo.setPreferredSize(new Dimension(110,20));
		combo.setFont(new Font("sansserif", Font.BOLD, 11));
		combo.addActionListener(this);
		comboPanel.add(combo);
		seqPanel.add(comboPanel);
		
				
		seq1 = createSeqData(V1GUIv,0);
		seq2 = createSeqData(V1GUIv,96);
		seq3 = createSeqData(V1GUIv,192);
		seq4 = createSeqData(V1GUIv,288);
		seq5 = createSeqData(V1GUIv,384);
		seq6 = createSeqData(V1GUIv,480);
		seq7 = createSeqData(V1GUIv,576);
		seq8 = createSeqData(V1GUIv,672);
		
		currentPanel = seq1;
		seqPanel.add(currentPanel);
		
		JPanel setupPanel = new JPanel();
		setupPanel.setLayout(new BoxLayout(setupPanel, BoxLayout.X_AXIS));
		setupPanel.setOpaque(false);			
		setupPanel.add(createConfig(V2GUIv,"Sequencer setup (left)"));
		setupPanel.add(createConfig(V3GUIv,"Sequencer setup (right)"));
		
		mainPanel.add(setupPanel);
		mainPanel.add(seqPanel);
	    this.add(mainPanel, BorderLayout.NORTH);
	}
	
	protected JPanel createConfig(Vector vGUI, String s) {		
		JPanel configPanel = new JPanel();
		configPanel.setLayout(new GridLayout(2,4));		
		configPanel.setBorder(BorderFactory.createEtchedBorder());
		configPanel.setBorder(BorderFactory.createTitledBorder(s));
		configPanel.setOpaque(false);
		configPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(0));
		configPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(4));
		configPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(1));		
		configPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(3));
		configPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(2));		
		return configPanel;
	}	

	protected JPanel createSeqData(Vector vGUI, int offset) {		
		JPanel seqPanel = new JPanel();
		seqPanel.setLayout(new GridBagLayout());		
		seqPanel.setOpaque(false);
		GridBagConstraints c = new GridBagConstraints();		
		c.fill = GridBagConstraints.HORIZONTAL;		
		
		String[] names = {"Step","Note","Octave","Param","Glide","Accent","Gate"};
		for(int row=0;row<7;row++) {
			c.gridx = 0;
			c.gridy = row;
			JLabel label = new JLabel(names[row]);
			label.setVerticalAlignment(JLabel.CENTER);
			label.setFont(new Font("serif",Font.BOLD,10));
			label.setOpaque(false);			
			label.setPreferredSize(new Dimension(35,10));
			seqPanel.add(label, c);
		}
		for(int col=0;col<16;col++) {
			c.gridx = col+1;
			c.gridy = 0;
			c.anchor = GridBagConstraints.CENTER;
			JLabel label = new JLabel(Integer.toString(col+1));
			label.setHorizontalAlignment(JLabel.CENTER);
			label.setFont(new Font("serif",Font.BOLD,10));
			label.setOpaque(false);			
			seqPanel.add(label, c);
		}
		for(int col=0;col<16;col++) {
			for(int row=0;row<6;row++) {
				c.gridx = col+1;
				c.gridy = row+1;
				seqPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(row+(6*col)+offset), c);				
				if (row==0) {
					((SIDSysexParameterControlKnob) vGUI.elementAt(row+(6*col)+offset)).setSnapvals(snapvals);
					((SIDSysexParameterControlKnob) vGUI.elementAt(row+(6*col)+offset)).setSnap(true);
				}
			}
		}		
		return seqPanel;
	}	
	
	public void actionPerformed(ActionEvent ae) {
		if (ae.getSource()==combo) {
			seqPanel.remove(currentPanel);
			switch (combo.getSelectedIndex()) {
				case 0:					
					currentPanel = seq1;
					break;
				case 1:					
					currentPanel = seq2;	
					break;
				case 2:
					currentPanel = seq3;
					break;
				case 3:
					currentPanel = seq4;				
					break;
				case 4:
					currentPanel = seq5;
					break;
				case 5:
					currentPanel = seq6;
					break;
				case 6:
					currentPanel = seq7;
					break;
				case 7:
					currentPanel = seq8;					
					break;
			}
			seqPanel.add(currentPanel);
			this.repaint();
		}
	}
}
