using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Useless.IO;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;

namespace Sample_IO
{
	[Serializable]
	public class MyItemType : ISerializable
	{
		public MyItemType()
		{
			// Empty constructor required to compile.
		}

		// The value to serialize.
		private string myProperty_value;

		public string MyProperty
		{
			get { return myProperty_value; }
			set { myProperty_value = value; }
		}

		// Implement this method to serialize data. The method is called 
		// on serialization.
		public void GetObjectData( SerializationInfo info, StreamingContext context )
		{
			// Use the AddValue method to specify serialized values.
			info.AddValue( "props", myProperty_value, typeof( string ) );

		}

		// The special constructor is used to deserialize values.
		public MyItemType( SerializationInfo info, StreamingContext context )
		{
			// Reset the property value using the GetValue method.
			myProperty_value = ( string )info.GetValue( "props", typeof( string ) );
		}
	}

	class Program
	{
		public static void SerializeItem( string fileName, IFormatter formatter )
		{
			// Create an instance of the type and serialize it.
			MyItemType t = new MyItemType();
			t.MyProperty = "Hello World";

			System.IO.FileStream s = new System.IO.FileStream( fileName, FileMode.Create );
			formatter.Serialize( s, t );
			s.Close();
		}


		public static void DeserializeItem( string fileName, IFormatter formatter )
		{
			System.IO.FileStream s = new System.IO.FileStream( fileName, FileMode.Open );
			MyItemType t = ( MyItemType )formatter.Deserialize( s );
			Console.WriteLine( t.MyProperty );
		}

		static void Main( string[] args )
		{
			try
			{
				// This is the name of the file holding the data. You can use any file extension you like.
				//string fileName = "dataStuff.myData";

				// Use a BinaryFormatter or SoapFormatter.
				//IFormatter formatter = new BinaryFormatter();
				//IFormatter formatter = new SoapFormatter();

				//SerializeItem( fileName, formatter ); // Serialize an instance of the class.
				//DeserializeItem( fileName, formatter ); // Deserialize the instance.
				//Console.WriteLine( "Done" );
				//Console.ReadLine();



				List<int> testval = new List<int>();
				testval.Add( 10 );
				testval.Add( 20 );
				testval.Add( 30 );

				HashSet<int> setVal = new HashSet<int>();
				setVal.Add( 50 );
				setVal.Add( 60 );
				setVal.Add( 70 );

				Dictionary<String, short> dictionaryVal = new Dictionary<string, short>();
				dictionaryVal.Add( "으하하", 10 );
				dictionaryVal.Add( "안녕", 20 );
				dictionaryVal.Add( "abc", 30 );

				//LinkedList<int> writeCollection = new LinkedList<int>();
				//writeCollection.AddLast( 33 );
				//writeCollection.AddLast( 44 );
				//writeCollection.AddLast( 55 );

				//Queue<int> writeCollection = new Queue<int>();
				//writeCollection.Enqueue( 33 );
				//writeCollection.Enqueue( 44 );
				//writeCollection.Enqueue( 55 );

				//SortedSet<int> writeCollection = new SortedSet<int>();
				//writeCollection.Add( 33 );
				//writeCollection.Add( 44 );
				//writeCollection.Add( 55 );

				Stack<int> writeCollection = new Stack<int>();
				writeCollection.Push( 33 );
				writeCollection.Push( 44 );
				writeCollection.Push( 55 );

				int[] writeArray = new int[ 3 ];
				writeArray[ 0 ] = 12;
				writeArray[ 1 ] = 22;
				writeArray[ 2 ] = 32;

				DynamicStream ds = new DynamicStream( 100 );

				Useless.IO.BinaryWriter bw = new Useless.IO.BinaryWriter( ds );
				//bw.Write( testval );
				//bw.Write( setVal );
				//bw.Write( dictionaryVal );
				//bw.Write( writeCollection );
				bw.Write( writeArray );

				ds.Position = 0;
                Useless.IO.BinaryReader br = new Useless.IO.BinaryReader( ds );
				//List<int> testval2 = new List<int>();
				//br.Read( ref testval2 );

				//LinkedList<int> readCollection = new LinkedList<int>();
				//Queue<int> readCollection = new Queue<int>();
				//SortedSet<int> readCollection = new SortedSet<int>();
				//Stack<int> readCollection = new Stack<int>();
				//SortedSet<int> readCollection = new SortedSet<int>();
				int[] arrayVal2 = new int[ 3 ];
				br.Read( ref arrayVal2 );
                //br.Read( ref readCollection );

				//HashSet<int> setVal2 = new HashSet<int>();
				//br.Read( ref setVal2 );

				//Dictionary<String, short> dictionaryVal2 = new Dictionary<string, short>();
				//br.Read( ref dictionaryVal2 );
            }
			catch( Exception )
			{

			}
		}
	}
}
