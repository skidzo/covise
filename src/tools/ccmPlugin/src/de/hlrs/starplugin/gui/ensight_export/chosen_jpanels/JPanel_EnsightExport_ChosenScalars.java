package de.hlrs.starplugin.gui.ensight_export.chosen_jpanels;

import de.hlrs.starplugin.gui.ensight_export.chosen_jpanels.scrollpanes.JScrollPane_ChosenScalarsPanel;
import de.hlrs.starplugin.util.GetGridBagConstraints;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 *
 * @author Weiss HLRS Stuttgart
 */
public class JPanel_EnsightExport_ChosenScalars extends JPanel {

    final GridBagLayout layout;
    private JLabel LabelChosenScalars;
    private JScrollPane_ChosenScalarsPanel EnsightExportChosenScalarsPanelScrollPane;

    public JPanel_EnsightExport_ChosenScalars() {
        //Layout für JPanel festlegn
        layout = new GridBagLayout();
        setLayout(layout);
        //bevorzugte Größe festlegen
        this.setPreferredSize(new Dimension(150, 400));

        //Headline (jLabel) erzeugen und hinzufügen
        LabelChosenScalars = new JLabel();
        LabelChosenScalars.setText("<html>Chosen&nbsp;Scalars</html>");
        GridBagConstraints GBCon = GetGridBagConstraints.get(0, 0, 0, 0, new Insets(
                0, 0, 0, 0),
                GridBagConstraints.NONE,
                GridBagConstraints.FIRST_LINE_START);
        this.add(LabelChosenScalars, GBCon);


        //JTree in ScrollPane erzugen und hinzufügen
        EnsightExportChosenScalarsPanelScrollPane = new JScrollPane_ChosenScalarsPanel();
        GBCon = GetGridBagConstraints.get(0, 1, 1, 1, new Insets(0, 0, 0, 0),
                GridBagConstraints.BOTH,
                GridBagConstraints.FIRST_LINE_START);
        GBCon.gridheight = GridBagConstraints.REMAINDER;

        this.add(EnsightExportChosenScalarsPanelScrollPane, GBCon);

    }

    public JScrollPane_ChosenScalarsPanel getEnsightExportChosenScalarsPanelScrollPane() {
        return EnsightExportChosenScalarsPanelScrollPane;
    }
}
