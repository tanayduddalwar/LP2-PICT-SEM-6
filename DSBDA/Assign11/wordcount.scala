import org.apache.spark.sql.SparkSession

val spark=SparkSession.builder.appName("WordCount").master("local[*]").getOrCreate()
import spark.implicits._

val lines=spark.read.text("D:/Downloads/inputtext.txt").as[String]
val words=lines.flatMap(_.split("\\s+")).filter(_ !="")
val word_count=words.groupByKey(identity).count()
word_count.show()
spark.stop()