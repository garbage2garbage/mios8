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

package org.midibox.sidedit.gui.multi;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JPanel;

import org.midibox.sidedit.SIDSysexParameterControl;
import org.midibox.sidedit.gui.WTTable;
import org.midibox.sidedit.gui.controls.SIDSysexParameterControlGUI;

public class WTGUI extends JPanel {
	protected WTGUI(Vector WTGUIv, Vector inst1, Vector inst2, Vector inst3,
			Vector inst4, Vector inst5, Vector inst6) {
		setLayout(new BorderLayout());
		this.setOpaque(false);

		JPanel panel1 = new JPanel();
		panel1.setLayout(new BoxLayout(panel1, BoxLayout.Y_AXIS));
		panel1.setOpaque(false);

		JPanel panel2 = new JPanel();
		panel2.setLayout(new GridLayout(1, 2));
		panel2.setOpaque(false);

		JPanel panel3 = new JPanel();
		panel3.setLayout(new GridLayout(6, 1));
		panel3.setOpaque(false);

		panel3.add(createWTE(inst1, "Wavetable 1", 41));
		panel3.add(createWTE(inst2, "Wavetable 2", 41));
		panel3.add(createWTE(inst3, "Wavetable 3", 41));
		panel3.add(createWTE(inst4, "Wavetable 4", 41));
		panel3.add(createWTE(inst5, "Wavetable 5", 41));
		panel3.add(createWTE(inst6, "Wavetable 6", 41));

		panel2.add(panel3);

		// Setup the parameters that control begin, end and loop
		SIDSysexParameterControl[][] config = new SIDSysexParameterControl[6][3];
		config[0][0] = (((SIDSysexParameterControlGUI) inst1.elementAt(45))
				.getMidiParameter());
		config[0][1] = (((SIDSysexParameterControlGUI) inst1.elementAt(47))
				.getMidiParameter());
		config[0][2] = (((SIDSysexParameterControlGUI) inst1.elementAt(48))
				.getMidiParameter());
		config[1][0] = (((SIDSysexParameterControlGUI) inst2.elementAt(45))
				.getMidiParameter());
		config[1][1] = (((SIDSysexParameterControlGUI) inst2.elementAt(47))
				.getMidiParameter());
		config[1][2] = (((SIDSysexParameterControlGUI) inst2.elementAt(48))
				.getMidiParameter());
		config[2][0] = (((SIDSysexParameterControlGUI) inst3.elementAt(45))
				.getMidiParameter());
		config[2][1] = (((SIDSysexParameterControlGUI) inst3.elementAt(47))
				.getMidiParameter());
		config[2][2] = (((SIDSysexParameterControlGUI) inst3.elementAt(48))
				.getMidiParameter());
		config[3][0] = (((SIDSysexParameterControlGUI) inst4.elementAt(45))
				.getMidiParameter());
		config[3][1] = (((SIDSysexParameterControlGUI) inst4.elementAt(47))
				.getMidiParameter());
		config[3][2] = (((SIDSysexParameterControlGUI) inst4.elementAt(48))
				.getMidiParameter());
		config[4][0] = (((SIDSysexParameterControlGUI) inst5.elementAt(45))
				.getMidiParameter());
		config[4][1] = (((SIDSysexParameterControlGUI) inst5.elementAt(47))
				.getMidiParameter());
		config[4][2] = (((SIDSysexParameterControlGUI) inst5.elementAt(48))
				.getMidiParameter());
		config[5][0] = (((SIDSysexParameterControlGUI) inst6.elementAt(45))
				.getMidiParameter());
		config[5][1] = (((SIDSysexParameterControlGUI) inst6.elementAt(47))
				.getMidiParameter());
		config[5][2] = (((SIDSysexParameterControlGUI) inst6.elementAt(48))
				.getMidiParameter());

		panel2.add(createWTC2(WTGUIv, config, "Wavetable data"));

		panel1.add(panel2);

		this.add(panel1, BorderLayout.NORTH);
	}

	protected JPanel createWTE(Vector vGUI, String s, int offset) {
		JPanel wtePanel = new JPanel();
		wtePanel.setLayout(new BoxLayout(wtePanel, BoxLayout.X_AXIS));
		wtePanel.setBorder(BorderFactory.createEtchedBorder());
		wtePanel.setBorder(BorderFactory.createTitledBorder(s));
		wtePanel.setOpaque(false);

		wtePanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(3 + offset));

		JPanel subPanel = new JPanel(new GridLayout(1, 5));
		subPanel.setOpaque(false);
		subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(4 + offset));
		subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(6 + offset));
		subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(7 + offset));
		subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(0 + offset));
		// subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(1+offset));
		// // "to Left channel" not available for multi engine!
		// subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(2+offset));
		// // "to Right channel" not available for multi engine!
		// subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(5+offset));
		// // "Pos Controlled by MP" not available for multi engine!
		subPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(8 + offset));
		wtePanel.add(subPanel);

		return wtePanel;
	}

	protected JPanel createWTC1(Vector vGUI, String s) {
		JPanel wtcPanel = new JPanel();
		wtcPanel.setLayout(new GridLayout(3, 43));
		wtcPanel.setBorder(BorderFactory.createEtchedBorder());
		wtcPanel.setBorder(BorderFactory.createTitledBorder(s));
		wtcPanel.setOpaque(false);
		for (int c = 0; c < 128; c++) {
			wtcPanel.add((SIDSysexParameterControlGUI) vGUI.elementAt(c));
		}
		return wtcPanel;
	}

	protected JPanel createWTC2(Vector vGUI,
			SIDSysexParameterControl[][] config, String s) {
		JPanel wtcPanel = new JPanel();
		wtcPanel.setBorder(BorderFactory.createEtchedBorder());
		wtcPanel.setBorder(BorderFactory.createTitledBorder(s));
		wtcPanel.setOpaque(false);

		Vector v = new Vector();
		for (int c = 0; c < 128; c++) {
			v.add(((SIDSysexParameterControlGUI) vGUI.elementAt(c))
					.getMidiParameter());
		}
		wtcPanel.add(new WTTable(6, v, config));
		return wtcPanel;
	}
}
