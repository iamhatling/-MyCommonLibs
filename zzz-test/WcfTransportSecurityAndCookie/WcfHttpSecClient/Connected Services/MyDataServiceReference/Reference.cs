﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

namespace WcfHttpSecClient.MyDataServiceReference {
    using System.Runtime.Serialization;
    using System;
    
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.Runtime.Serialization", "4.0.0.0")]
    [System.Runtime.Serialization.DataContractAttribute(Name="MyData", Namespace="http://schemas.datacontract.org/2004/07/WcfTransportSecurityLibrary")]
    [System.SerializableAttribute()]
    public partial class MyData : object, System.Runtime.Serialization.IExtensibleDataObject, System.ComponentModel.INotifyPropertyChanged {
        
        [System.NonSerializedAttribute()]
        private System.Runtime.Serialization.ExtensionDataObject extensionDataField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private long OffsetField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private long LengthField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private string NameField;
        
        [System.Runtime.Serialization.OptionalFieldAttribute()]
        private byte[] BufferField;
        
        [global::System.ComponentModel.BrowsableAttribute(false)]
        public System.Runtime.Serialization.ExtensionDataObject ExtensionData {
            get {
                return this.extensionDataField;
            }
            set {
                this.extensionDataField = value;
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute()]
        public long Offset {
            get {
                return this.OffsetField;
            }
            set {
                if ((this.OffsetField.Equals(value) != true)) {
                    this.OffsetField = value;
                    this.RaisePropertyChanged("Offset");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=1)]
        public long Length {
            get {
                return this.LengthField;
            }
            set {
                if ((this.LengthField.Equals(value) != true)) {
                    this.LengthField = value;
                    this.RaisePropertyChanged("Length");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=2)]
        public string Name {
            get {
                return this.NameField;
            }
            set {
                if ((object.ReferenceEquals(this.NameField, value) != true)) {
                    this.NameField = value;
                    this.RaisePropertyChanged("Name");
                }
            }
        }
        
        [System.Runtime.Serialization.DataMemberAttribute(Order=3)]
        public byte[] Buffer {
            get {
                return this.BufferField;
            }
            set {
                if ((object.ReferenceEquals(this.BufferField, value) != true)) {
                    this.BufferField = value;
                    this.RaisePropertyChanged("Buffer");
                }
            }
        }
        
        public event System.ComponentModel.PropertyChangedEventHandler PropertyChanged;
        
        protected void RaisePropertyChanged(string propertyName) {
            System.ComponentModel.PropertyChangedEventHandler propertyChanged = this.PropertyChanged;
            if ((propertyChanged != null)) {
                propertyChanged(this, new System.ComponentModel.PropertyChangedEventArgs(propertyName));
            }
        }
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    [System.ServiceModel.ServiceContractAttribute(ConfigurationName="MyDataServiceReference.IMyDataService", SessionMode=System.ServiceModel.SessionMode.NotAllowed)]
    public interface IMyDataService {
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IMyDataService/Begin", ReplyAction="http://tempuri.org/IMyDataService/BeginResponse")]
        void Begin();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IMyDataService/Begin", ReplyAction="http://tempuri.org/IMyDataService/BeginResponse")]
        System.Threading.Tasks.Task BeginAsync();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IMyDataService/GetData", ReplyAction="http://tempuri.org/IMyDataService/GetDataResponse")]
        WcfHttpSecClient.MyDataServiceReference.MyData GetData(WcfHttpSecClient.MyDataServiceReference.MyData myData);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IMyDataService/GetData", ReplyAction="http://tempuri.org/IMyDataService/GetDataResponse")]
        System.Threading.Tasks.Task<WcfHttpSecClient.MyDataServiceReference.MyData> GetDataAsync(WcfHttpSecClient.MyDataServiceReference.MyData myData);
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IMyDataService/End", ReplyAction="http://tempuri.org/IMyDataService/EndResponse")]
        void End();
        
        [System.ServiceModel.OperationContractAttribute(Action="http://tempuri.org/IMyDataService/End", ReplyAction="http://tempuri.org/IMyDataService/EndResponse")]
        System.Threading.Tasks.Task EndAsync();
    }
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public interface IMyDataServiceChannel : WcfHttpSecClient.MyDataServiceReference.IMyDataService, System.ServiceModel.IClientChannel {
    }
    
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.CodeDom.Compiler.GeneratedCodeAttribute("System.ServiceModel", "4.0.0.0")]
    public partial class MyDataServiceClient : System.ServiceModel.ClientBase<WcfHttpSecClient.MyDataServiceReference.IMyDataService>, WcfHttpSecClient.MyDataServiceReference.IMyDataService {
        
        public MyDataServiceClient() {
        }
        
        public MyDataServiceClient(string endpointConfigurationName) : 
                base(endpointConfigurationName) {
        }
        
        public MyDataServiceClient(string endpointConfigurationName, string remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public MyDataServiceClient(string endpointConfigurationName, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(endpointConfigurationName, remoteAddress) {
        }
        
        public MyDataServiceClient(System.ServiceModel.Channels.Binding binding, System.ServiceModel.EndpointAddress remoteAddress) : 
                base(binding, remoteAddress) {
        }
        
        public void Begin() {
            base.Channel.Begin();
        }
        
        public System.Threading.Tasks.Task BeginAsync() {
            return base.Channel.BeginAsync();
        }
        
        public WcfHttpSecClient.MyDataServiceReference.MyData GetData(WcfHttpSecClient.MyDataServiceReference.MyData myData) {
            return base.Channel.GetData(myData);
        }
        
        public System.Threading.Tasks.Task<WcfHttpSecClient.MyDataServiceReference.MyData> GetDataAsync(WcfHttpSecClient.MyDataServiceReference.MyData myData) {
            return base.Channel.GetDataAsync(myData);
        }
        
        public void End() {
            base.Channel.End();
        }
        
        public System.Threading.Tasks.Task EndAsync() {
            return base.Channel.EndAsync();
        }
    }
}
