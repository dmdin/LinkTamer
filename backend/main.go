package main

import (
	"fmt"
	"github.com/Dikower/LinkTamer/backend/database"
	"github.com/Dikower/LinkTamer/backend/link"
	"github.com/gofiber/fiber/v2"
	"github.com/gofiber/fiber/v2/middleware/cors"
	"github.com/gofiber/fiber/v2/middleware/logger"
	"github.com/jinzhu/gorm"
)

func setupRoutes(app *fiber.App) {
	app.Post("/new", link.New)
	app.Get("/get/:shorten", link.Get)
	//app.Get("/", link.GetAll)
}

func initDatabase() {
	var err error
	database.DBConn, err = gorm.Open("sqlite3", "links.db")
	if err != nil {
		panic("failed to connect database")
	}
	fmt.Println("Connection Opened to Database")

}

func main() {
	app := fiber.New()
	app.Use(logger.New())
	app.Use(cors.New(cors.Config{
		AllowOrigins: "http://localhost:5000, http://linktamer.xyz, https://linktamer.xyz",
		AllowHeaders: "Origin, Content-Type, Accept, Content-Length, Date, Vary",
	}))
	initDatabase()
	database.DBConn.AutoMigrate(&link.Link{})
	fmt.Println("Database Migrated")
	setupRoutes(app)
	err := app.Listen(":8000")

	if err != nil {
		panic(err)
	}
}
