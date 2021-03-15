using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using INFITF;
using MECMOD;
using PARTITF;
using ProductStructureTypeLib;
using HybridShapeTypeLib;

namespace CATIA_Automation
{
    public partial class FormSelect : Form
    {
        INFITF.Application CATIA;
        CATBaseDispatch _objLine;
        Reference _objRef;
        public FormSelect()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void buttonInitCatia_Click(object sender, EventArgs e)
        {
            
            try
            {
                //CATIA=(INFITF.Application)Marshal.GetActiveObject("CATIA.Application");
                CATIA = (INFITF.Application)System.Runtime.InteropServices.Marshal.GetActiveObject("Catia.Application");
            }
            catch
            {
                 Type oType = System.Type.GetTypeFromProgID("CATIA.Application");
                 CATIA = (INFITF.Application)Activator.CreateInstance(oType);
                 CATIA.Visible = true;
            }

        }

        private void buttonSelect_Click(object sender, EventArgs e)
        {
            Document doc = CATIA.ActiveDocument;
            Selection lineSelect = doc.Selection;

            object[] selType = new object[2]
            {
                CATSelectionFilter.MonoDim.ToString(),
                CATSelectionFilter.MonoDimInfinite.ToString()
            };

            string status = lineSelect.SelectElement2(selType, "Select element", false);
            if (status=="cancel")
            {
                return;
            }

            
            _objLine = lineSelect.Item2(1).Value;
            _objRef = lineSelect.Item2(1).Reference;

            textBoxSelect.Text = lineSelect.Item2(1).Reference.DisplayName;

            lineSelect.Clear();
        }

        private void buttonRename_Click(object sender, EventArgs e)
        {
            Document doc = CATIA.ActiveDocument;
            PartDocument partDoc = (PartDocument)doc;
            Part part = partDoc.Part;
            HybridShapeFactory factory = (HybridShapeFactory)part.HybridShapeFactory;
            //Reference objRef = part.CreateReferenceFromObject(_objRef);
            factory.ChangeFeatureName(_objRef,textBoxSelect.Text);
        }
    }
}
