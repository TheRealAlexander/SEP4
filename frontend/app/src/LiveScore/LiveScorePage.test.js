import { render, screen } from "@testing-library/react";
import "@testing-library/jest-dom/extend-expect";
import React from "react";
import userEvent from "@testing-library/user-event";
import LiveScorePage from "./LiveScorePage";
import LiveScoreService from "../Services/LiveScoreService";

jest.mock("../Services/LiveScoreService");

test("renders LiveScorePage and checks match click", async () => {
  // Mock matches data
  const matches = [
    {
      id: 1,
      name: "Match 1",
      date: "2022-01-01",
      score: "1-0",
      field: "Field 1",
      startTime: "10:00",
    },
    // Add more matches as needed
  ];

  // Mock the getAllMatches function to return a resolved promise with the matches data
  LiveScoreService.getAllMatches.mockImplementation(() =>
    Promise.resolve(matches)
  );

  // Render the component
  render(<LiveScorePage />);

  // Check if the match is rendered
  const matchElement = await screen.findByText(/Match 1/i);
  expect(matchElement).toBeInTheDocument();

  // Click on the match and check if the additional details are rendered
  userEvent.click(matchElement);
  await screen.findByText(/Field: Field 1/i);
  await screen.findByText(/Start Time: 10:00/i);

  // Click on the match again and check if the additional details are hidden
  userEvent.click(matchElement);
  expect(screen.queryByText(/Field: Field 1/i)).not.toBeInTheDocument();
  expect(screen.queryByText(/Start Time: 10:00/i)).not.toBeInTheDocument();
});

// New test: Empty state
test("renders message when there are no matches", async () => {
  // Mock the getAllMatches function to return a resolved promise with an empty array
  LiveScoreService.getAllMatches.mockResolvedValue([]);

  // Render the component
  render(<LiveScorePage />);

  // Check if the empty message is displayed
  const emptyMessage = await screen.findByText(/No matches/i);
  expect(emptyMessage).toBeInTheDocument();
});

// New test: Error state
test("renders error message when there is an error fetching data", async () => {
  // Mock the getAllMatches function to return a rejected promise with an error message
  LiveScoreService.getAllMatches.mockImplementation(() =>
    Promise.reject(new Error("Network Error"))
  );

  // Render the component
  render(<LiveScorePage />);

  // Check if the error message is displayed
  const errorMessage = await screen.findByText(/Error: Network Error/i);
  expect(errorMessage).toBeInTheDocument();
});
