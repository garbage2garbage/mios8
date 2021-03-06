/*
 * @(#)HexFileUploadGUI.java	beta8	2006/04/23
 *
 * Copyright (C) 2008   Adam King (adamjking@optusnet.com.au)
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

package org.midibox.mios.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.Iterator;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComponent;
import javax.swing.JFileChooser;
import javax.swing.JFormattedTextField;
import javax.swing.JLabel;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.JTextPane;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.event.PopupMenuEvent;
import javax.swing.event.PopupMenuListener;
import javax.swing.text.Style;
import javax.swing.text.StyleConstants;
import javax.swing.text.StyleContext;
import javax.swing.text.StyledDocument;

import org.midibox.mios.HexFileUpload;
import org.midibox.utils.gui.HexFormatterFactory;
import org.midibox.utils.gui.ImageLoader;
import org.midibox.utils.gui.SimpleFileChooserFilter;
import org.midibox.utils.gui.SplitButton;

public class HexFileUploadGUI extends JPanel implements ActionListener,
		ChangeListener, Observer {

	private JPopupMenu MRUPopupMenu;

	private SplitButton openMRUButton;

	private static int maxMRU = 10;

	private static String currentDirectory = "";

	private static Vector MRU = new Vector();

	private static JFileChooser fc = null;

	private HexFileUpload hexFileUpload;

	// GUI components

	private JButton browseButton;

	private JTextField fileName;

	private JButton startButton;

	private JButton stopButton;

	private JButton queryButton;

	private JTextPane progressMessageTextArea;

	private JLabel deviceIDLabel;

	private JSpinner deviceIDSpinner;

	private JRadioButton smartModeButton;

	private JRadioButton dumbModeButton;

	private ButtonGroup buttonGroup;

	private JCheckBox waitForUploadRequestCheck;

	private JCheckBox MIOS32Check;

	private JLabel delayTimeLabel;

	private JSpinner delayTimeSpinner;

	public HexFileUploadGUI(HexFileUpload hexUploadTask) {
		super(new BorderLayout());

		this.hexFileUpload = hexUploadTask;
		hexUploadTask.addObserver(this);

		Insets insets = new Insets(2, 2, 2, 2);

		browseButton = new JButton("Hex File", ImageLoader
				.getImageIcon("open.png"));
		browseButton.setActionCommand("browse");
		browseButton.addActionListener(this);
		browseButton.setMargin(insets);
		browseButton.setToolTipText("Open Hex File");

		fileName = new JTextField();
		fileName.setEditable(false);

		File file = hexFileUpload.getFile();

		if (file != null) {

			fileName.setText(file.getPath());
		}

		startButton = new JButton("Start");
		startButton.setActionCommand("start");
		startButton.addActionListener(this);
		startButton.setEnabled(false);

		stopButton = new JButton("Stop");
		stopButton.addActionListener(this);
		stopButton.setActionCommand("stop");

		queryButton = new JButton("Query");
		queryButton.addActionListener(this);
		queryButton.setActionCommand("query");
		queryButton.setEnabled(false);

		startButton.setAlignmentX(Component.LEFT_ALIGNMENT);
		stopButton.setAlignmentX(Component.LEFT_ALIGNMENT);
		queryButton.setAlignmentX(Component.LEFT_ALIGNMENT);

		JPanel fileButtonsPanel = new JPanel(new BorderLayout(2, 0));

		MRUPopupMenu = new JPopupMenu();
		MRUPopupMenu.addPopupMenuListener(new PopupMenuListener() {

			public void popupMenuCanceled(PopupMenuEvent e) {

			}

			public void popupMenuWillBecomeInvisible(PopupMenuEvent e) {

			}

			public void popupMenuWillBecomeVisible(PopupMenuEvent e) {

				HexFileUploadGUI.this.buildMRUMenu(MRUPopupMenu);

			}
		});

		openMRUButton = new SplitButton(browseButton, MRUPopupMenu);
		openMRUButton.setRollover(true);

		fileButtonsPanel.add(openMRUButton, BorderLayout.WEST);
		fileButtonsPanel.add(fileName, BorderLayout.CENTER);
		fileButtonsPanel.setBorder(BorderFactory.createEmptyBorder(7, 7, 5, 7));

		JPanel controlButtonsPanel = new JPanel();
		controlButtonsPanel.setLayout(new BoxLayout(controlButtonsPanel,
				BoxLayout.LINE_AXIS));
		controlButtonsPanel.add(startButton);
		controlButtonsPanel.add(Box.createRigidArea(new Dimension(15, 0)));
		controlButtonsPanel.add(stopButton);
		controlButtonsPanel.add(Box.createHorizontalGlue());
		controlButtonsPanel.add(queryButton);
		controlButtonsPanel.add(Box.createHorizontalGlue());
		controlButtonsPanel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5,
				5));

		JPanel progressMessagePanel = new JPanel();
		progressMessagePanel.setLayout(new BoxLayout(progressMessagePanel,
				BoxLayout.PAGE_AXIS));

		progressMessageTextArea = new JTextPane();
		progressMessageTextArea.setBackground(Color.WHITE);

		StyledDocument doc = progressMessageTextArea.getStyledDocument();

		Style def = StyleContext.getDefaultStyleContext().getStyle(
				StyleContext.DEFAULT_STYLE);

		Style regular = doc.addStyle("regular", def);
		StyleConstants.setFontFamily(def, "Monospaced");

		Style s = doc.addStyle("ack", regular);
		StyleConstants.setForeground(s, new Color(0, 150, 50));

		s = doc.addStyle("error", regular);
		StyleConstants.setForeground(s, new Color(150, 0, 50));

		progressMessageTextArea.setEditable(false);
		JScrollPane progressMessageTextAreaScrollPane = new JScrollPane(
				progressMessageTextArea);
		progressMessageTextAreaScrollPane
				.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

		// Make preferred width smaller than the other panel's minimum width.
		progressMessageTextAreaScrollPane.setPreferredSize(new Dimension(300,
				100));

		progressMessagePanel.add(progressMessageTextAreaScrollPane);
		progressMessagePanel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5,
				5));

		JPanel controlPanel = new JPanel();
		controlPanel
				.setLayout(new BoxLayout(controlPanel, BoxLayout.PAGE_AXIS));
		controlPanel.add(controlButtonsPanel);
		controlPanel.add(progressMessagePanel);

		controlPanel.setBorder(BorderFactory.createCompoundBorder(BorderFactory
				.createEmptyBorder(5, 5, 5, 5), BorderFactory
				.createTitledBorder("Upload Control")));

		JPanel protocolPanel = new JPanel();

		protocolPanel.setBorder(BorderFactory.createCompoundBorder(
				BorderFactory.createEmptyBorder(5, 5, 5, 5), BorderFactory
						.createTitledBorder("Upload Options")));

		protocolPanel.setLayout(new GridBagLayout());

		GridBagConstraints gbc = new GridBagConstraints();
		gbc.gridx = 0;
		gbc.gridy = 0;
		gbc.gridwidth = 1;
		gbc.gridheight = 1;
		gbc.anchor = GridBagConstraints.WEST;
		gbc.insets = new Insets(2, 2, 2, 2);

		deviceIDLabel = new JLabel("Device ID:");
		protocolPanel.add(deviceIDLabel, gbc);
		gbc.gridx++;

		deviceIDSpinner = new JSpinner(new SpinnerNumberModel(hexFileUpload
				.getDeviceID(), 0, 127, 1));
		deviceIDSpinner.addChangeListener(this);
		JSpinner.DefaultEditor editor = (JSpinner.DefaultEditor) deviceIDSpinner
				.getEditor();
		JFormattedTextField tf = editor.getTextField();
		tf.setFormatterFactory(new HexFormatterFactory());
		protocolPanel.add(deviceIDSpinner, gbc);
		gbc.gridx++;

		gbc.insets = new Insets(2, 15, 2, 2);

		MIOS32Check = new JCheckBox("MIOS32", hexFileUpload.isMIOS32Mode());
		MIOS32Check.addActionListener(this);
		protocolPanel.add(MIOS32Check, gbc);

		gbc.gridx = 0;
		gbc.gridy++;

		gbc.gridwidth = 4;
		waitForUploadRequestCheck = new JCheckBox(
				"Wait for upload request before starting upload", hexFileUpload
						.isWaitForUploadRequest());
		waitForUploadRequestCheck.addActionListener(this);
		protocolPanel.add(waitForUploadRequestCheck, gbc);
		gbc.gridy++;

		smartModeButton = new JRadioButton(
				"Smart Mode - Use feedback from core", hexFileUpload
						.getUploadMode() == HexFileUpload.SMART_MODE);
		smartModeButton.addActionListener(this);
		protocolPanel.add(smartModeButton, gbc);
		gbc.gridy++;

		dumbModeButton = new JRadioButton(
				"Manual Mode - Don't use feedback from core", hexFileUpload
						.getUploadMode() == HexFileUpload.DUMB_MODE);
		dumbModeButton.addActionListener(this);
		protocolPanel.add(dumbModeButton, gbc);
		gbc.gridy++;

		buttonGroup = new ButtonGroup();
		buttonGroup.add(dumbModeButton);
		buttonGroup.add(smartModeButton);

		gbc.insets = new Insets(2, 15, 2, 2);

		JPanel timePanel = new JPanel(new FlowLayout(0, 5, 0));

		delayTimeLabel = new JLabel("Delay between SysEx messages (ms):");
		timePanel.add(delayTimeLabel);

		delayTimeSpinner = new JSpinner(new SpinnerNumberModel(hexFileUpload
				.getDelayTime(), 10, 2000, 1));
		delayTimeSpinner.addChangeListener(this);
		timePanel.add(delayTimeSpinner);

		protocolPanel.add(timePanel, gbc);

		gbc.gridy++;

		gbc.weighty = 1.0;
		protocolPanel.add(new JPanel(), gbc);

		add(fileButtonsPanel, BorderLayout.PAGE_START);
		add(controlPanel, BorderLayout.CENTER);
		add(protocolPanel, BorderLayout.EAST);

		updateUploadControls();
	}

	private void buildMRUMenu(JComponent menu) {

		menu.removeAll();

		Iterator it = MRU.iterator();

		while (it.hasNext()) {

			final JMenuItem menuItem = new JMenuItem((String) it.next());

			menuItem.addActionListener(new ActionListener() {

				public void actionPerformed(ActionEvent ae) {

					File file = new File(menuItem.getText());

					openHexFile(file);
				}
			});

			menu.add(menuItem, 0);
		}
	}

	public static void saveMRU(String file) {

		MRU.remove(file);

		MRU.add(file);

		for (int i = MRU.size() - maxMRU; i > 0; i--) {

			MRU.removeElementAt(i - 1);
		}
	}

	public static String getCurrentDirectory() {
		return currentDirectory;
	}

	public static void setCurrentDirectory(String currentDirectory) {
		HexFileUploadGUI.currentDirectory = currentDirectory;
	}

	public HexFileUpload getHexFileUpload() {
		return hexFileUpload;
	}

	protected void openHexFile() {

		if (fc == null) {
			fc = new JFileChooser(currentDirectory);
			SimpleFileChooserFilter fileFilter = new SimpleFileChooserFilter(
					"Hex files", "hex", "Compliled Hex file");
			fc.addChoosableFileFilter(fileFilter);
			fc.setAcceptAllFileFilterUsed(false);
		}

		File noFile = new File("");
		File noFiles[] = { noFile };
		fc.setSelectedFile(noFile);
		fc.setSelectedFiles(noFiles);

		int nRetVal = fc.showOpenDialog(this);

		if (nRetVal == JFileChooser.APPROVE_OPTION) {
			File file = fc.getSelectedFile();

			openHexFile(file);

			currentDirectory = fc.getCurrentDirectory().toString();
		}
	}

	protected void openHexFile(File file) {

		if (file.exists()) {

			hexFileUpload.setFile(file);

			saveMRU(file.getPath());

		} else {
			JOptionPane.showMessageDialog(this, "Hex file no longer exists",
					"File does not exist", JOptionPane.ERROR_MESSAGE);
		}
	}

	public static Vector getMRU() {
		return MRU;
	}

	public void updateUploadControls() {

		boolean bUploading = (!hexFileUpload.isCancelled() && !hexFileUpload
				.isDone());

		deviceIDLabel.setEnabled(!bUploading);
		deviceIDSpinner.setEnabled(!bUploading);

		MIOS32Check.setEnabled(!bUploading);

		if (hexFileUpload.isMIOS32Mode()) {
			smartModeButton.setEnabled(false);
			dumbModeButton.setEnabled(false);
			waitForUploadRequestCheck.setEnabled(false);
			delayTimeLabel.setEnabled(false);
			delayTimeSpinner.setEnabled(false);
		} else {
			smartModeButton.setEnabled(!bUploading);
			dumbModeButton.setEnabled(!bUploading);

			waitForUploadRequestCheck.setEnabled(!bUploading);

			delayTimeLabel
					.setEnabled(!bUploading
							&& hexFileUpload.getUploadMode() == HexFileUpload.DUMB_MODE);

			delayTimeSpinner
					.setEnabled(!bUploading
							&& hexFileUpload.getUploadMode() == HexFileUpload.DUMB_MODE);
		}

		startButton.setEnabled(!bUploading && hexFileUpload.getFile() != null);
		stopButton.setEnabled(bUploading);
		queryButton.setEnabled(!bUploading && hexFileUpload.isMIOS32Mode());
	}

	public void stateChanged(ChangeEvent e) {

		Object source = e.getSource();

		if (source == deviceIDSpinner) {
			hexFileUpload.setDeviceID(((Integer) deviceIDSpinner.getValue())
					.intValue());

		} else if (source == delayTimeSpinner) {
			hexFileUpload.setDelayTime(((Integer) delayTimeSpinner.getValue())
					.intValue());
		}
	}

	public void actionPerformed(ActionEvent e) {

		String command = e.getActionCommand();
		Object source = e.getSource();

		if (command.equals("start")) {
			if (hexFileUpload.fileChanged()) {

				int nRet = JOptionPane.showConfirmDialog(null, "The file '"
						+ hexFileUpload.getFile().getPath()
						+ "' has changed.\n"
						+ "Do you wish to reload this file?",
						"File has changed", JOptionPane.YES_NO_OPTION,
						JOptionPane.INFORMATION_MESSAGE, null);

				if (nRet == JOptionPane.YES_OPTION) {
					hexFileUpload.setFile(hexFileUpload.getFile());
				}
			}

			progressMessageTextArea.setText("");

			Thread t = new Thread() {
				public void run() {
					hexFileUpload.createUpload();
				}
			};

			// t.setDaemon(true);
			t.start();

		} else if (command.equals("query")) {
			progressMessageTextArea.setText("");

			Thread t = new Thread() {
				public void run() {
					hexFileUpload.createQuery();
				}
			};

			// t.setDaemon(true);
			t.start();

		} else if (command.equals("stop")) {
			hexFileUpload.cancel();

		} else if (command.equals("browse")) {
			openHexFile();

		} else if (source == smartModeButton || source == dumbModeButton) {
			hexFileUpload
					.setUploadMode(smartModeButton.isSelected() ? HexFileUpload.SMART_MODE
							: HexFileUpload.DUMB_MODE);

		} else if (source == MIOS32Check) {
			hexFileUpload.setMIOS32Mode(MIOS32Check.isSelected());

		} else if (source == waitForUploadRequestCheck) {
			hexFileUpload.setWaitForUploadRequest(waitForUploadRequestCheck
					.isSelected());
		}
	}

	public void update(Observable observable, Object object) {
		if (observable == hexFileUpload) {
			if (object == HexFileUpload.MESSAGES
					|| object == HexFileUpload.WORKER) {
				while (!hexFileUpload.getMessages().isEmpty()) {
					try {
						String message = (String) hexFileUpload.getMessages()
								.removeFirst();
						StyledDocument doc = progressMessageTextArea
								.getStyledDocument();
						String style = "regular";

						if (message.startsWith("Error")
								|| message.startsWith("Received error")
								|| message.endsWith("errors")
								|| message.endsWith("Error")) {
							style = "error";
						} else if (message.startsWith("Received")) {
							style = "ack";
						}

						doc.insertString(doc.getLength(), message + "\n", doc
								.getStyle(style));
						progressMessageTextArea.setCaretPosition(doc
								.getLength());
					} catch (Exception e) {

					}
				}
			} else if (object == HexFileUpload.FILE) {
				fileName.setText(hexFileUpload.getFile().getPath());

			} else if (object == HexFileUpload.DELAY_TIME) {
				delayTimeSpinner.setValue(new Integer(hexFileUpload
						.getDelayTime()));

			} else if (object == HexFileUpload.DEVICE_ID) {
				deviceIDSpinner.setValue(new Integer(hexFileUpload
						.getDeviceID()));

			} else if (object == HexFileUpload.UPLOAD_MODE) {
				smartModeButton
						.setSelected(hexFileUpload.getUploadMode() == HexFileUpload.SMART_MODE);

				dumbModeButton
						.setSelected(hexFileUpload.getUploadMode() == HexFileUpload.DUMB_MODE);

			} else if (object == HexFileUpload.MIOS32_MODE) {
				MIOS32Check.setSelected(hexFileUpload.isMIOS32Mode());
			} else if (object == HexFileUpload.WAIT_FOR_UPLOAD) {
				waitForUploadRequestCheck.setSelected(hexFileUpload
						.isWaitForUploadRequest());
			}

			updateUploadControls();
		}
	}
}