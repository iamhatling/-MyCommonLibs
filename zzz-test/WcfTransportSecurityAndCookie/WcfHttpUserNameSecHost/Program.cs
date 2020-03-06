﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;
using WcfTransportSecurityCommon;

namespace WcfHttpUserNameSecHost
{
    class Program
    {
        static void Main(string[] args)
        {
            using (ServiceHost host = new ServiceHost(typeof(WcfTransportSecurityLibrary.MyDataService)))
            {
                //host.Credentials.ServiceCertificate.Certificate = new System.Security.Cryptography.X509Certificates.X509Certificate2(@"f:\smart-wcf-client.p12", "ccc");
                var userAuthn = host.Credentials.UserNameAuthentication;
                userAuthn.UserNamePasswordValidationMode = System.ServiceModel.Security.UserNamePasswordValidationMode.Custom;
                userAuthn.CustomUserNamePasswordValidator = new MyCustomUserNameValidator();

                host.Open();
                var uris = host.Description.Endpoints.Select(ep => ep.ListenUri.AbsoluteUri);
                foreach (string uri in uris)
                {
                    Console.WriteLine($"Service started at {uri} on {DateTime.Now}");
                }
                Console.WriteLine($"Press ENTER to end service...");
                Console.ReadLine();
            }
        }
    }
}
