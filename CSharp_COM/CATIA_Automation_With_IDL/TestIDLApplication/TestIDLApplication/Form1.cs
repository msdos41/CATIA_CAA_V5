using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using INFITF;
using MECMOD;
using PARTITF;
using ProductStructureTypeLib;
using HybridShapeTypeLib;
using TestIDLFrm;

namespace TestIDLApplication
{
    public partial class Form1 : Form
    {
        INFITF.Application CATIA;
        
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonTest_Click(object sender, EventArgs e)
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

            Document doc = CATIA.ActiveDocument;
            PartDocument partDoc = (PartDocument)doc;
            Part part = partDoc.Part;
            string sAlias = "CAAIATestInterfaceVB";
            //InstanceFactory fact = (InstanceFactory)part.GetCustomerFactory(ref sAlias);
            CAAIATestInterfaceVB testIntf = (CAAIATestInterfaceVB)part.GetCustomerFactory(ref sAlias);
            //try
            //{
            //    testIntf.CreateObject();
            //}
            //catch (System.Exception ex)
            //{
            	
            //}
            string isName="";
            string osName = "";
            testIntf.TestFunction(ref isName, ref osName);
        }
    }
}